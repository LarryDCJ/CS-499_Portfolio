from pymongo import MongoClient


class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, username, password):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 

        # self.client = MongoClient('mongodb://localhost:35468')
        self.client = MongoClient(
            'mongodb://%s:%s@localhost:35468/?authMechanism=DEFAULT&authSource=AAC' % (username, password))
        self.database = self.client['AAC']

    # Complete this create method to implement the C in CRUD.
    def create(self, data: dict):
        # If data is passed to insert
        if data is not None:
            # Insert the data into DB, insert method returns the id of the new document
            id = self.database.animals.insert(data)  # data should be dictionary            
            # If an ID is returned, the insert was successful
            if id:
                return True
            # If insert was unsuccessful, return false
            else:
                raise Exception("The insert was unsuccessful")
                return False
        else:
            # If no data is passed to insert, return false
            raise Exception("Nothing to save, because data parameter is empty")
            return False

    # Create method to implement the R in CRUD.
    def read(self, data: dict):
        # If data is passed to read
        if data is not None:
            # find returns a cursor containing all results 
            result = self.database.animals.find(data)
            if result is not None:
                return result
            else:
                raise Exception("No documents were returned, check db connection")
        # If no data is passed to read, return false
        else:
            raise Exception("Nothing to read, because data parameter is empty")

    # Update method to implement the U in CRUD.
    def update(self, filter=None, newData=None):
        # If data is passed to update
        if newData is not None:
            result = self.database.animals.update_one(filter, newData)
            # Return the result of the update
            return self.database.animals.find(filter)
        # If no data is passed to insert, return false
        else:
            raise Exception("Nothing to update, because data parameter is empty")

    # Delete method to implement the D in CRUD.
    def delete(self, data: dict):
        # If data is passed to delete
        if data is not None:
            # Return the result of the delete command, either the result or an error
            print(self.database.animals.find_one(data))
            return self.database.animals.delete_one(data)
        # If no data is passed to insert, return false
        else:
            raise Exception("Nothing to delete, because data parameter is empty")
