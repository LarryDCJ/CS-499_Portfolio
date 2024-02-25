package com.lcawley.authentication;

import java.io.*;
import java.util.Scanner;

public class Authentication {
    // We could also mount files in a known location for docker volumes in the future,
    // adding the directory to the jvm classpath
    private static final String CREDENTIALS_FILE = "/credentials.txt";
    private static final Integer USERNAME_POSITION = 0;
    private static final Integer HASHPASS_POSITION = 1;
    private static final Integer ROLE_POSITION = 3;


    public static void main(String[] args) throws IOException {
        Scanner scnr = new Scanner(System.in);
        boolean isRunning = true;
    
        while (isRunning) {
            String userNameInput = promptUsername(scnr);
            if ("q".equals(userNameInput)) {
                isRunning = false;
                continue;
            }
    
            String userPassInput = promptPassword(scnr);
            String hashedPassword = getHashedPass(userPassInput);
    
            if (checkCredentials(userNameInput, hashedPassword)) {
                processUserRole(scnr, userNameInput);
            } else {
                System.out.println("Invalid username or password.");
            }
        }
    }

    private static String promptUsername(Scanner scnr) {
        System.out.print("Enter username or 'q' to quit: ");
        return scnr.nextLine();
    }
    
    private static String promptPassword(Scanner scnr) {
        System.out.print("Enter password: ");
        return scnr.nextLine();
    }
    /*
     * checkCredentials ensures the given username matches with the MD5 hash version of the provided password
     * @parameter userName is the user provided username from credentials.txt
     * @paramenter passwordHash is verified against the hashed password from the credentials.txt, formed from the plaintext password
     */
    public static boolean checkCredentials(String userName, String passwordHash) throws IOException {
        try (Scanner credentialSS = new Scanner(Authentication.class.getResourceAsStream(CREDENTIALS_FILE))) {
            while (credentialSS.hasNextLine()) {
                String[] credentials = credentialSS.nextLine().split("\t");
                if (credentials[0].equals(userName) && credentials[HASHPASS_POSITION].equals(passwordHash)) {
                    return true;
                }
            }
        }
        return false;
    }

    private static void processUserRole(Scanner scnr, String username) throws IOException {
        String role = fetchUserRole(username);
        
        handleUserActions(role);
    }

    private static String fetchUserRole(String username) throws IOException {
        try (Scanner credentialSS = new Scanner(Authentication.class.getResourceAsStream(CREDENTIALS_FILE))) {
           
            while (credentialSS.hasNextLine()) {
                String[] credentials = credentialSS.nextLine().split("\t");
                if (credentials[USERNAME_POSITION].equals(username)) {
                    return credentials[ROLE_POSITION].replaceAll("\"", "");
                }
            }
        }
        return null;
    }
    

    /*
     * Greets the user after logging in.
     * @parameter role is a string representing the role of the user from the credentials file
     * and is used to retrieve the greeting for that particular role
     */
    public static String handleUserActions(String role) throws IOException {
        // Greetins are stored in files like admin.txt in the resources dir
        String roleFile = "/" + role + ".txt";
        try (InputStream roleStream = Authentication.class.getResourceAsStream(roleFile);
             Scanner roleScanner = new Scanner(roleStream)) {
            
            while (roleScanner.hasNextLine()) {
                return roleScanner.nextLine();
            }
        }
        return null;
    }
    
    private static String getHashedPass(String plainPassword){
        MD5Digest md5 = new MD5Digest();
        md5.setMD5Password(plainPassword);
        return md5.getUserPassMD5();
    }
}
