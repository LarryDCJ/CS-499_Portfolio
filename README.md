# Larry Cawley - SNHU CS-499


## Zoo Authentication App

### About This Application

### Setup

Download SDKMan [here](https://sdkman.io/install).

Download and Install Java 21.0.2 via SDKMan

`sdk install java 21.0.2-open`

Download Maven 3.9.6

```
curl https://dlcdn.apache.org/maven/maven-3/3.9.6/binaries/apache-maven-3.9.6-bin.tar.gz --output  apache-maven-3.9.6-bin.tar.gz
```
Install Maven
```
 tar xzvf apache-maven-3.9.6-bin.tar.gz
```



## Plans to Refactor
### Deficiencies
credentials.txt referenced as a local file
no consistent build
vaguely named variables
large blocks of logic that could be refactored
no java documentation
no unit testing

### Enhancements
The Zoo Authentication System from the IT-245 course demonstrates my skills in software engineering and design. For enhancement, I plan to refactor the code for modularity, update to Java 21 from 1.8, implement testing, and convert the project to utilize Maven with a docker deployment. Updating to Java 21 allows utilization of the latest APIs and language features, such as pattern matching and records, which streamline code and enhance readability. For testing, I'll integrate unit tests for individual components and integration tests to ensure the entire system works cohesively, thereby increasing reliability. Utilizing Maven will streamline build processes and dependency management while Docker will be employed for deployment, enhancing portability and scalability of the application. These updates will showcase my ability to design secure and scalable systems, aligning with course outcomes in software engineering and security principles.




<!-- TODO -->

Delete this old reference from the paper from the original IT-245 course

Problem Statement: 
My goal was to create an authentication system based on a user gaining access to specified areas of a computer system based on their roles, determined by the credentials they enter when initially logging in. Users should also have the option to exit this program via inputs or switch roles via logging in after a successful attempt has occurred.
Overall Progress:
	The live chat helped me considerably this week. I was on the path to hardcoding roles and realized this did not mesh with the intention of the assignment. It made it a lot more static vs the dynamic nature of what good code should be. The start of my confusion came when incorporating the MD5 hash file. 
Pseudocode:
Pseudocode for Option 1: Authentication System
WHILE username and password attempts are less than/equal to 3
WHILE username DOES NOT equal exit
READ username
READ password
CHECK password using MD5 hash
CHECK username with credential file
CHECK password with credential file
IF Username/Password are correct
ALL user access to specified role
IF Username/Password are incorrect
INCREMENT attempts
IF username and password attempts are more than 3
NOTIFY user of 3 incorrect attempts
EXIT program
IF user input equals EXIT
EXIT Program
Methods and Classes:	
	As shown in the tutorial/weekly discussion video, I utilized a User Role class, used for getting the role name from the credentials file and returning it, stripped of extraneous whitespaces/tabs. It then sets the role to the “roleInfo” variable. This is then used to select the proper access file, depending on which user logs in. 
	I also used the MD5Digest class. This is used to run the input password through an MD5 hash and format it appropriately. This is used to verify against the credential file to ensure the proper password input and the password input space isn’t blank, via the “j” variable.
Error Documentation:
	My biggest point of confusion came with the MD5Digest class. I found myself researching inputs into functions, the returns from functions and the proper syntax in Java. I also had some issues with exiting the program after a user successfully logged in. This was due to me not providing a way to input other text following a proper login. 
Solution Documentation:
Reviewing Zybooks and paying close attention to the tutorials helped me solve my issues and align the proper variables with what I was attempting to pass to the class and return from it. Based on reviewing several www.stackoverflow.com issues and the provided tutorials, I found my loops were not properly nested and led to issues that I had yet to discover as well.

 

