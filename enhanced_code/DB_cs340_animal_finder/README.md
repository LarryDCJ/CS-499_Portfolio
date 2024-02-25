[Repo Home](README.md) - [Software Design & Engineering](../../enhanced_code/SDE_it245_zoo_auth/SDE.md) - [Data Structures and Algorithms](../../enhanced_code/DSALGO_cs260_binary_search_tree/ADS.md) - [Databases](../../enhanced_code/DB_cs340_animal_finder/DB.md) - [Code Review](../../CR.md)

# Animal Database

### [Initial Code Review Video](https://www.youtube.com/watch?v=phOuFE7oz80)

## About This Application

The Animal Finder Application is a web-based platform designed for managing an animal database. Leveraging Flask for the web server and MongoDB for the database, it supports CRUD operations—Create, Read, Update, Delete—on animal records. This application offers an intuitive interface for users to interact with the database, facilitating the addition, retrieval, modification, and deletion of animal data efficiently.

## Setup
### Prerequisites
* Docker
* Python 3.8 or newer
* Pipenv or Virtualenv

### Installation Steps
* Clone the repository to your local machine.
* Navigate to the project directory and install dependencies using pip install -r requirements.txt.
* Use docker-compose up to start the MongoDB container.
* Run python server.py to launch the Flask application.

### Usage
To interact with the application, navigate to http://localhost:5000 in your web browser. The application's interface allows for the addition, viewing, editing, and deletion of animal records through intuitive web forms.

For API usage, refer to the following endpoints:

/create for adding new records.
/read for retrieving records.
/update for updating existing records.
/delete for removing records.
Testing
To ensure the application's reliability, a suite of automated tests is provided. Run pytest in the project directory to execute these tests, verifying the functionality of both the backend logic and the web endpoints.
