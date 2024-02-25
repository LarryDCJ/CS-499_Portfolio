# Animal Shelter Management System

This is a web-based application for managing records in an animal shelter.
It utilizes Flask as the server/frontend, Python as the backend, and MongoDB for data storage, enabling users to perform CRUD operations.

* *animal_finder.py*: Contains the AnimalShelter class responsible for CRUD operations with MongoDB.
* *server.py*: Sets up the Flask application and defines routes for the web interface.
* *animal_finder_test.py*: Includes tests for both the Flask web routes and the backend AnimalShelter class methods.
## Installation

### Prerequisites

- Python 3.8 or newer.
- Docker and Docker Compose.
- Virtual environment tool (e.g., venv for Python).

### Setup Instructions

1. **Clone the Repository**

   Clone the project repository to your local machine and navigate into the project directory.

    ```bash
    git clone <url>
    cd <dir>
   ```

2. **Create and Activate Virtual Environment**

   Use venv (or any virtual environment manager of your choice) to create and activate a virtual environment.

   For venv:
   ```bash
    python3 -m venv venv
    # .\venv\Scripts\activate   # Windows
    # source venv/bin/activate  # Linux
    ```

3. **Install Dependencies**
    ```bash
    pip install -r requirements.txt
    ```
4. **Start MongoDB**

    ```bash
    docker-compose up -d
    ```

5. **Start Flask Server**

    ```bash
    python server.py
    ```

    ```bash
    pytest animal_finder_test.py
    ```
