package authentication;

import java.io.*;
import java.util.Scanner;
import java.io.FileInputStream;

public class Authentication {

    public static void main(String[] args) throws Exception, IOException {

        FileInputStream credentialStream = null; //Stream to read credentials
        FileInputStream fileRoleStream; // stream to read roles
        Scanner credentialSS; //scanner to input credentials
        Scanner roleSS; // scanner to input roles
        Scanner scnr = new Scanner(System.in);

        String userNameInput; //user provided name to search credentials files
        String userPassInput; //user provided password to search credentials files
        String userPassHashed;
        String roleInfo;
        String roleFile;
        String credWord = "none";
        String logoutInfo;
        char programStatus = 'a'; //exits program if it equals 'q'
        int i; //username input from credential file
        int j; //user pass input from credential file
        int n; //attempt counter
        boolean userNameCheck = false; //check username input exists
        boolean userPassCheck = false; //check user pass input exists

        MD5Digest userPass = new MD5Digest();
        UserRole findRole = new UserRole();


        while (programStatus != 'q') { //If the user has not chosen to quit the program

            for (n = 3; n > 0; n--) { //increments incorrect user/pass inputs

                if (n < 3) {

                    System.out.println("Username or Password cannot be found. Please try again.");
                }

                System.out.println("Enter user name: ");
                userNameInput = scnr.nextLine(); //scans user input
                System.out.println("Enter password: ");
                userPassInput = scnr.nextLine(); //scans user password

                userPass.setMD5Password(userPassInput); //passes userpassword input to MD5 Hash
                userPassHashed = userPass.getUserPassMD5(); //assigns MD5 return to new variable

                credentialStream = new FileInputStream("/Users/larrydcj/IdeaProjects/Authentication/credentials.txt"); //reads credential files
                credentialSS = new Scanner(credentialStream); //reads credential input

                while (credentialSS.hasNextLine()) { //while there are bytes in the credential scanner, this loops will occur

                    credWord = credentialSS.nextLine(); //assigns credential words to lines scanned
                    i = credWord.indexOf(userNameInput); //shows username input isn't blank
                    j = credWord.indexOf(userPassHashed); //shows user password isn't blank

                    if (userNameCheck = false) {
                        break;
                    } else if (i >= 0) {

                        userNameCheck = true;
                        if (j >= 0) {

                            userPassCheck = true;
                            n = 0;
                            break;
                        } else {
                            userPassCheck = false;
                        }
                        break;
                    }
                    else {
                        userNameCheck = false;
                    }
                }

                if ((n < 2) && (n > 0)) {
                    System.out.println("You have tried and failed 3 times. You lose. Good day Sir/Ma'am.");
                    System.out.println("Exiting Program");
                    programStatus = 'q';
                }
            }


            if (programStatus != 'q') {

                findRole.setUserRole(credWord); // retrieves user role from credentials file
                roleInfo = findRole.getUserRole(); // reassigned user role to variable to access proper files
                roleFile = ("/Users/larrydcj/IdeaProjects/Authentication/" + roleInfo +".txt"); //path to access proper file based on  userrole/roleInfo variable
                fileRoleStream = new FileInputStream(roleFile); //inputs role files
                roleSS = new Scanner(fileRoleStream); //reads input role files
                System.out.println("\n");

                while (roleSS.hasNextLine()) { //runs while role scanner has input

                    System.out.println(roleSS.nextLine());
                }
                System.out.println("\n");
                fileRoleStream.close();

                System.out.println("Enter q to logout. Enter n for new user login.");
                logoutInfo = scnr.nextLine(); //receives user input to exit program
                if (logoutInfo.charAt(0) == 'q') {
                    programStatus = 'q'; //sets program to 'q' to exit
                    System.out.println("Goodbye");
                }
            }

        }

        if(programStatus == 'q') {
            System.exit(0);

        }
        System.out.println("\n");

credentialStream.close();

return;

    }

}