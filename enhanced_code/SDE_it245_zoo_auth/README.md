[Repo Home](README.md) - [Software Design & Engineering](../../enhanced_code/SDE_it245_zoo_auth/SDE.md) - [Data Structures and Algorithms](../../enhanced_code/DSALGO_cs260_binary_search_tree/ADS.md) - [Databases](../../enhanced_code/DB_cs340_animal_finder/DB.md) - [Code Review](../../CR.md)

# Binary Search Tree

### [Initial Code Review Video](https://www.youtube.com/watch?v=GDugSRiZp2w)

## About This Application

The Binary Search Tree (BST) Application is a high-performance, scalable data management system implemented in C++. It leverages AVL tree balancing to maintain O(log n) time complexity for insertions, deletions, and search operations, ensuring optimal efficiency. This project exemplifies best practices in algorithm design and software development, focusing on efficiency, security, and maintainability.

## Setup
### Prerequisites
* Java JDK 21
* Maven
* Docker (optional for containerization)

### Installation Steps
* Clone the repository to your local machine.
* Navigate to the project directory.
* Run mvn clean install to build the project and resolve dependencies.
* To run the application, execute java -jar target/zoo-authentication-system.jar.

### Docker Deployment (Optional)
* Ensure Docker is installed and running on your system.
* Use the provided Dockerfile to build the Docker image with docker build -t zoo-authentication-system ..
* Run the application in a container using docker run -d zoo-authentication-system.

## Usage
After launching the application, users can log in with their credentials. Access to functionalities is based on user roles, with specific features available to administrators, veterinarians, and zookeepers respectively.
