package authentication;

import java.security.MessageDigest;

public class MD5Digest {

	private String userPassMD5;

	void setMD5Password(String userPassInput) throws Exception {
      
		MessageDigest md = MessageDigest.getInstance("MD5");
		md.update (userPassInput.getBytes());
		byte[] digest = md.digest();
      StringBuffer sb = new StringBuffer();
		for (byte b : digest) {
			sb.append(String.format("%02x", b & 0xff));
		}

		userPassMD5 = sb.toString();
		this.userPassMD5 = userPassMD5;

	}

	public String getUserPassMD5() {
		return userPassMD5;

	}

}