package authentication;

public class UserRole {

   private String userRole;
   private int k;

   void setUserRole (String credWord) {

      k = credWord.lastIndexOf("\t");
      userRole = credWord.substring(k + 1, credWord.length());

   }

   public String getUserRole() {

      return userRole;
   }
}
