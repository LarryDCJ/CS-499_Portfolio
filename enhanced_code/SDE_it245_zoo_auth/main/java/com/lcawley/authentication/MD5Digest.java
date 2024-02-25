package com.lcawley.authentication;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5Digest {

    private String userPassMD5;

    void setMD5Password(String userPassInput) {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(userPassInput.getBytes());
            byte[] digest = md.digest();
            StringBuilder sb = new StringBuilder();
            for (byte b : digest) {
                sb.append(String.format("%02x", b & 0xff));
            }
            userPassMD5 = sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
    }

    public String getUserPassMD5() {
        return userPassMD5;
    }
}
