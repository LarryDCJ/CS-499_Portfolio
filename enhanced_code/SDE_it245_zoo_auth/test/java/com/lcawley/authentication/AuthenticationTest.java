package com.lcawley.authentication;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import java.io.IOException;

public class AuthenticationTest {
    /**
     * Tests that expected username and hashed passwords are valid, testing the credential process.
     * @throws IOException
     */

    @Test
    public void testCheckCredentials() throws IOException {
        // usernames and password hashes from the credentials file
        String username1 = "griffin.keyes";
         // hash for "alphabet soup"
        String passwordHash1 = "108de81c31bf9c622f76876b74e9285f";
        
        String username2 = "rosario.dawson";
        // hash for "animal doctor"
        String passwordHash2 = "3e34baa4ee2ff767af8c120a496742b5"; 
        
        // Check if the credentials are valid
        boolean isValidUser1 = Authentication.checkCredentials(username1, passwordHash1);
        boolean isValidUser2 = Authentication.checkCredentials(username2, passwordHash2);
        
        // Assert that the credentials should be valid
        Assertions.assertTrue(isValidUser1, "Credentials for user1 should be valid");
        Assertions.assertTrue(isValidUser2, "Credentials for user2 should be valid");
    }

    @Test
    public void testHandleUserActions() throws IOException {
        // Test the user actions with a known valid role
        String testRole = "admin";
        String expectedOutput = "Hello, System Admin!";

        String greeting = Authentication.handleUserActions(testRole);

        // Check if the output contains expected lines from the role file
        Assertions.assertEquals(greeting, expectedOutput);

    }
}
