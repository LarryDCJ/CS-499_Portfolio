[Repo Home](README.md) - [Software Design & Engineering](../../enhanced_code/SDE_it245_zoo_auth/SDE.md) - [Data Structures and Algorithms](../../enhanced_code/DSALGO_cs260_binary_search_tree/ADS.md) - [Databases](../../enhanced_code/DB_cs340_animal_finder/DB.md) - [Code Review](../../CR.md)

[Software Design & Engineering Readme](./README.md)

<h1>Software Design & Engineering</h1>

The Zoo Authentication System from the IT-245 course demonstrated newly gained skills in software engineering and design. For enhancement in CS-499, I’ve refactored the code to move logic into separate methods. This will lead to an easier time sharing logic between classes as the code is further refined as well as sharing parts of the library externally. I also wrote tests with separate testing resources to ensure any changes don’t break our functionality.
The repo was also updated from Java 1.8 to 21 for security as well as being set up as a Maven project. For testing, I added unit tests for public methods to ensure the code changes don’t hinder the application in the future, increasing reliability. Utilizing Maven also helps speed up the build process and simplifies dependency management while Docker will be employed for deployment, enhancing portability and scalability of the application. My remaining steps for this project are to separate methods into classes per primary data types such as MD5 and also preparing a class to house user specific methods pertaining to username, password, and roles to keep our main.java file as slim as possible. 

