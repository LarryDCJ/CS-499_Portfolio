import json

from bson import ObjectId
from pymongo import MongoClient
from pymongo.errors import PyMongoError


class JSONEncoder(json.JSONEncoder):
    """Extends json-encoder class to serialize ObjectId to string."""
    def default(self, o):
        if isinstance(o, ObjectId):
            return str(o)
        return json.JSONEncoder.default(self, o)


class AnimalShelter:
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        # Initialize the MongoClient in the constructor
        self.client = MongoClient(
            'mongodb://%s:%s@localhost:27017/?authMechanism=DEFAULT&authSource=AAC' % (username, password))
        self.database = self.client['AAC']

    # create
    def create(self, data: dict):
        """Create a new animal entry in the database"""
        if data is not None:
            try:
                # Use insert_one instead of deprecated insert method
                result = self.database.animals.insert_one(data)
                # insert_one returns an InsertOneResult object, which includes the inserted_id
                if result.inserted_id:
                    return True
            except PyMongoError as e:
                # Catch any pymongo errors and raise as a more informative exception
                raise Exception(f"Insert failed: {e}")
        else:
            # Raise an exception if no data is provided
            raise ValueError("Nothing to create: data parameter is empty")

            # If we reach this point, something went wrong with the insert
        return False

    # Create method to implement the R in CRUD.
    def read(self, query: dict):
        """Read data from MongoDB"""
        if query is not None:
            try:
                result = self.database.animals.find(query)
                # Convert the cursor to a list of dictionaries and serialize ObjectId to string
                return json.loads(JSONEncoder().encode([doc for doc in result]))
            except Exception as e:
                raise Exception(f"Read failed: {e}")
        else:
            raise ValueError("Nothing to read, because query parameter is empty")

    def update(self, field=None, newData=None):
        """Updates an entry, filtering by parameter"""
        # If data is passed to update
        if newData is not None:
            result = self.database.animals.update_one(field, newData)
            # Return the result of the update
            return self.database.animals.find(field)
        # If no data is passed to insert, return false
        else:
            raise Exception("Nothing to update, because data parameter is empty")

    def delete(self, data: dict):
        """Deletes the specified animal from the database."""
        if data is not None:
            # Return a boolean for the delete command
            result = self.database.animals.delete_one(data)
            if result is not None:
                return True
            return False
        # If no data is passed to insert, return false
        else:
            raise Exception("Nothing to delete, because data parameter is empty")

    def create_text_index(self, field_list):
        """Creates a text index on the specified fields."""
        self.database.animals.create_index([(field, "name", "age_upon_outcome", "animal_type") for field in field_list])

    def text_search(self, text_query):
        """Performs a full-text search on the collection."""
        return self.database.animals.find({"$text": {"$search": text_query}})
