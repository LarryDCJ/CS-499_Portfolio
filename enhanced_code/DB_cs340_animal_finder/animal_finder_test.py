# test_animal_shelter.py
import pytest
from flask import json
from server import app
from animal_finder import AnimalShelter  # Adjust import as necessary


@pytest.fixture(scope="module")
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client


@pytest.fixture(scope="module")
def shelter():
    """Fixture to create an AnimalShelter instance."""
    # Setup
    username = "aacuser"
    password = "3935"
    test_shelter = AnimalShelter(username, password)
    return test_shelter


def test_create(shelter):
    """Test the create method."""
    data = {'age_upon_outcome': '12 years', 'animal_type': 'Cat', 'name': 'TestCat'}
    assert shelter.create(data)


def test_read(shelter):
    """Test the read method."""
    query = {'name': 'TestCat'}
    assert shelter.read is not None


def test_update(shelter):
    """Test the update method."""
    targetToUpdate = {'name': 'TestCat'}
    newData = {"$set": {'age_upon_outcome': '2 years'}}
    shelter.update(targetToUpdate, newData)
    assert shelter.read({'name': 'TestCat', 'age_upon_outcome': '2 years'})


def test_delete(shelter):
    """Test the delete method."""
    to_delete = {'name': 'TestCat', 'age_upon_outcome': '2 years'}
    assert shelter.delete(to_delete)


def test_create_endpoint(client):
    """Test the /create endpoint."""
    data = {'age_upon_outcome': '12 years', 'animal_type': 'Dog', 'name': 'TestDog'}
    response = client.post('/create', data=data)
    assert response.status_code == 200
    assert json.loads(response.data)['success'] == True


def test_read_endpoint(client):
    """Test the /read endpoint."""
    response = client.get('/read?name=TestDog')
    assert response.status_code == 200
    results = json.loads(response.data)
    assert any(d['name'] == 'TestDog' for d in results)


def test_update_endpoint(client):
    """Test the /update endpoint."""
    filter_query = json.dumps({'name': 'TestDog'})
    new_values = json.dumps({"$set": {'age_upon_outcome': '3 years'}})
    response = client.post('/update', data={'filter': filter_query, 'newValues': new_values})
    assert response.status_code == 200
    # Verify update with a read operation or check response


def test_delete_endpoint(client):
    """Test the /delete endpoint."""
    data = {'name': 'TestDog', 'age_upon_outcome': '3 years'}
    response = client.post('/delete', data=data)
    assert response.status_code == 200
    assert json.loads(response.data)['success'] == True
    # Optionally, verify deletion with a subsequent read operation
