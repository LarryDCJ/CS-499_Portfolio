import json

from flask import Flask, request, jsonify, render_template
from animal_finder import AnimalShelter  # Adjust the import path as needed

app = Flask(__name__)

# Initialize your AnimalShelter instance
shelter = AnimalShelter('aacuser', '3935')  # Use your credentials


@app.route('/')
def index():
    return render_template('index.html')  # A simple HTML form for CRUD operations


@app.route('/create', methods=['POST'])
def create_animal():
    data = request.form.to_dict()
    result = shelter.create(data)
    return jsonify({'success': result}), 200 if result else 400


@app.route('/read', methods=['GET'])
def read_animal():
    query = request.args.to_dict()
    results = list(shelter.read(query))
    for result in results:
        result['_id'] = str(result['_id'])  # Convert ObjectId to string
    return jsonify(results), 200 if results else 404


@app.route('/update', methods=['POST'])
def update_animal():
    filter_query = request.form['filter']
    new_values = request.form['newValues']
    # Assuming filter_query and new_values need to be converted from string to dictionary
    filter_query = json.loads(filter_query)
    new_values = json.loads(new_values)
    shelter.update(filter_query, new_values)
    updated_docs = list(shelter.read(filter_query))
    return jsonify([doc for doc in updated_docs]), 200 if updated_docs else 400



@app.route('/delete', methods=['POST'])
def delete_animal():
    query = request.form.to_dict()
    result = shelter.delete(query)
    return jsonify({'success': result}), 200 if result else 400


if __name__ == '__main__':
    app.run(debug=True)
