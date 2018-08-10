/*
 * CS 362 Software Engineering II
 * Summer 2018
 * Group Project:
 * - Kevin Bray
 * - Stephanie Ayala
 * - Greg Doolittle
 *
 * Final Project Part B
 *
 * You are provided a buggy version of URLValidator. You need to find out as many bugs as you can in
 * this bad URLValidator. In the Part-A, I have provided the current test framework that Apache
 * commons team had to test URLValidator. We need to assume that all those tests don’t exist. Your team
 * is a testing company and client comes to you with URLValidator implementation and asks for your help
 * to make it bug-free. You need to just concentrate on isValid method, the one that is tested in
 * testIsValid() method.
 *
 * Your task is to find out two the bugs, find out failure causes and provide bug
 * reports. You don’t need to fix any of the bugs. Developers will do it.
 *
 */

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing

/*
 * Call the valid method of URLValidator with different possible
 * valid/invalid inputs and see if you find a failure.
 */
	   UrlValidator urlVal = new UrlValidator(null, null, 0L);
	   boolean isValid;
	   boolean allPassed = true;
	   boolean expected = true;
	   String url;
	   
	   String goodUrl[] = {	           
			   "http://www.google.com",
			   "http://www.cnn.com:80",
			   "http://www.asdf.biz",
			   "http://www.google.com:0",
			   "http://www.google.com:80",
			   "http://www.google.com:800",
			   "http://www.google.com:8000",
			   "http://www.google.com:65535",
			   "http://www.google.com:80",
			   "http://www.google.com",
			   "ftp://www.google.com",		
			   "https://www.google.com",
			   "https://www.google.com/",
			   "https://www.google.com:80/",
			   "https://www.google.com/search",
			   "https://www.google.com/search.html",
			   "https://www.google.com/?asdf=fdas",
			   "https://www.google.com/?%20",
			   "https://www.google.com/?asdf$",			   
			   "https://www.google.com/?asd%20fdsa",
			   "http://www.geocities.com/nkotb_fan_club",			   
			   "http://www.geocities.com/~nkotb_fan_club",							// ~ failing test
			   "http://192.168.1.1", 
			   "http://192.168.1.0", 
			   "http://0.0.0.0", 
			   "http://255.255.255.255", 
			   "http://192.168.1.1:80",
			   "http://[FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:80/index.html",
		       "http://[1080:0:0:0:8:800:200C:417A]/index.html",
	           "http://[3ffe:2a00:100:7031::1]",
	           "http://[1080::8:800:200C:417A]/foo",
	           "http://[2010:836B:4179::836B:4179]"
	   };
	   
	   String badUrl[] = {
			   "asdf",
			   "junk://www.google.com",
			   "http://www.google.com:65536",
			   "http://www.google.com:65536/",
			   "https://www.google.com/?asd fdsa",
			   "http://192.168.1.256", 
			   "http://192.168.256.256", 
			   "http://256.257.258.259", 
			   "http://256.256.256.256", 
			   "http://192.168.1.256:80",
			   "http://FEDC:BA98:7654:3210:FEDC:BA98:7654:3210:80/index.html",
		       "http://1080:0:0:0:8:800:200C:417A/index.html",
	           "http://3ffe:2a00:100:7031::1",
	           "http://1080::8:800:200C:417A/foo",
	           "http://2010:836B:4179::836B:4179"	   
	   };
	   
	   System.out.println("**************  MANUAL TESTING  **************");
	   System.out.println("PASS/FAIL | EXPECTED | ACTUAL | URL");
	   System.out.println("----------------------------------------------------");
	   
	   for (int i = 0; i < goodUrl.length; i++) {
		   url = goodUrl[i];
		   isValid = urlVal.isValid(url);
		   expected = true;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("VALID    | ");
		   if (isValid) {
			   System.out.print("VALID   | ");
			   System.out.println(url);
		   } else {
			   System.out.print("INVAL   | ");
			   System.out.println(url);
			   allPassed = false;
		   }
	   }
	   
	   System.out.print("\n");
	   
	   for (int i = 0; i < badUrl.length; i++) {
		   url = badUrl[i];
		   isValid = urlVal.isValid(url);
		   expected = false;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("INVAL    | ");
		   if (isValid) {
			   System.out.print("VALID   | ");
			   System.out.println(url);
			   allPassed = false;
		   } else {
			   System.out.print("INVAL   | ");
			   System.out.println(url);
		   }
	   }
	   
	   assertTrue(allPassed);
   }
	   

   
   public void testScheme()
   {
	 //You can use this function to implement your First Partition testing	   

	   boolean isValid;
	   boolean allPassed = true;
	   boolean expected;
	   String scheme;
	   
	  // *** Test scheme component ***
	   String allowedSchemes[] = {
			   "http",
			   "https",
			   "ftp",
			   "randomscheme"
	   };
	   
	   String goodSchemes[] = {
			   "http",
			   "https",
			   "ftp",
			   "HTTP",
			   "FTP",
			   "HTTPS",
			   "randomscheme"
	   };
	   
	   String badSchemes[] = {
			   "asdffdsa",
			   "3ht",
			   "asdf"

	   };
	   
	   // using this constructor allows you to pass in a list of good schemes.  
	   // the 0L flag gives no options such as ALLOW_ALL_SCHEMES or ALLOW_2_SLASHES
	   UrlValidator urlVal = new UrlValidator(allowedSchemes, 0L);
	   
	   System.out.println("\n**************  TESTING SCHEME COMPONENTS **************");
	   System.out.println("PASS/FAIL | EXPECTED | ACTUAL | SCHEME");
	   System.out.println("----------------------------------------------------");
	   
	   for (int i = 0; i < goodSchemes.length; i++) {
		   scheme = goodSchemes[i];
		   isValid = urlVal.isValidScheme(scheme);
		   expected = true;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("VALID    | ");
		   if (isValid) {
			   System.out.print("VALID  | ");
			   System.out.println(scheme);
		   } else {
			   System.out.print("INVAL  | ");
			   System.out.println(scheme);
			   allPassed = false;
		   }
	   }
	   
	   System.out.print("\n");
	   
	   for (int i = 0; i < badSchemes.length; i++) {
		   scheme = badSchemes[i];
		   isValid = urlVal.isValidScheme(scheme);
		   expected = false;
		   if (isValid == expected) {
			   System.out.print("PASSED    | ");
		   } else {
			   System.out.print("FAILED    | ");
		   }
		   System.out.print("INVAL    | ");
		   if (isValid) {
			   System.out.print("VALID  | ");
			   System.out.println(scheme);
			   allPassed = false;
		   } else {
			   System.out.print("INVAL  | ");
			   System.out.println(scheme);
		   }
	   }
	   
	   assertTrue(allPassed);

   }
   
   
   public void testYourSecondPartition(){
	   //You can use this function to implement your Second Partition testing
	   /* come up with good input partitioning. Try to provide a varying set of inputs that partition the
	    * overall input set well. Did you find any failures? You can call valid method once or more for each
	    * partition.
	    */

	   /*
	    *  This method covers unit testing on UrlValidator.isValidPath, which is
	    *  a helper method used by UrlValidator.isValid, to determine if the
	    *  path section of a URL is valid or not.
	    */

	   UrlValidator urlVal = new UrlValidator(null, null, 0L);

	   // PATH testing
	   String sectionName = "path";

	   System.out.println("\n\n**************  TESTING " + sectionName.toUpperCase() + " COMPONENT **************\n"
			+ "PASS/FAIL | EXPECTED | ACTUAL | " + sectionName.toUpperCase() + "\n"
			+ "----------------------------------------------------");

	   String[] goodPaths = {
			   "/path" ,
			   "/foo/bar",
			   "/fooo/bar/baz",
			   "/proper/commons-validator/apidocs/src-html/org/apache/commons/validator/routines/UrlValidator.html",
			   "/aburasa/CS362-004-S2018",
			   "filepath"
	   };

	   int goodCount = 0;
	   for (int i = 0; i < goodPaths.length; i++) {
		   String passOrFail = (urlVal.isValidPath(goodPaths[i])) ? "PASSED" : "FAILED";
		   String validity = (urlVal.isValidPath(goodPaths[i])) ? "VALID" : "INVAL";
		   String expectation = "VALID";
		   System.out.println(passOrFail + "    | " + expectation + "    | " + validity + "   | " + goodPaths[i]);
		   if (!urlVal.isValidPath(goodPaths[i])) {
			   goodCount++;
		   }
	   }
	   System.out.println("Ran " + goodPaths.length + " positive " + " " + sectionName + " tests...");
	   if (goodCount > 0) {
		   for (int i = 0; i < goodCount; i++) {
			   System.out.print("+");
		   }
		   System.out.println(" Found " + goodCount + " positive " + sectionName + " failure(s).");
	   } else {
		   System.out.println("No positive path failure(s) found!");
	   }


	   String[] badPaths = {
			   "/p ath" ,
			   "/fo :8000 o/bar",
			   "/fooo/../../index.html",
			   "/fooo/..///../bar/baz",
			   "/../baz",
			   "/ o o 0 0 0 0 ",
			   "192.168.0.0"
	   };
	   int badCount = 0;
	   for (int i = 0; i < badPaths.length; i++) {
		   String passOrFail = (!urlVal.isValidPath(badPaths[i])) ? "PASSED" : "FAILED";
		   String validity = (urlVal.isValidPath(badPaths[i])) ? "VALID" : "INVAL";
		   String expectation = "INVAL";
		   System.out.println(passOrFail + "    | " + expectation + "    | " + validity + "   | " + badPaths[i]);
		   if (urlVal.isValidPath(badPaths[i])) {
			   badCount++;
		   }
	   }
	   System.out.println("Ran " + badPaths.length + " negative " + " " + sectionName + "  tests...");
	   if (badCount > 0) {
		   for (int i = 0; i < badCount; i++) {
			   System.out.print("-");
		   }
		   System.out.println(" Found " + badCount + " negative " + " " + sectionName + " failure(s).");
	   } else {
		   System.out.println("No negative path failure(s) found!");
	   }

	   int totalCount = goodCount + badCount;
	   if (totalCount > 0) {
		   System.out.println(totalCount + " " + sectionName + " failures overall.");
	   }
	   assert(totalCount == 0);
   }
   //You need to create more test cases for your Partitions if you need to 
   public void testYourThirdPartition()
   {
	   /*
	    *  This method covers unit testing on UrlValidator.isValidQuery, which is
	    *  a helper method used by UrlValidator.isValid, to determine if the
	    *  query section of a URL is valid or not.
	    */

	   UrlValidator urlVal = new UrlValidator(null, null, 0L);
	   // QUERY testing

	   String sectionName = "query";

	   System.out.println("\n\n**************  TESTING " + sectionName.toUpperCase() + " COMPONENT **************\n"
			+ "PASS/FAIL | EXPECTED | ACTUAL | " + sectionName.toUpperCase() + "\n"
			+ "----------------------------------------------------");

	   String[] goodQueries = {
			   "?asdf" ,
			   "?foo=bar",
			   "?a=1&b=2&c=3",
			   "?q=urlvalidator+apache+commons",
	   };
	   int goodCount = 0;
	   for (int i = 0; i < goodQueries.length; i++) {
		   String passOrFail = (urlVal.isValidQuery(goodQueries[i])) ? "PASSED" : "FAILED";
		   String validity = (urlVal.isValidQuery(goodQueries[i])) ? "VALID" : "INVAL";
		   String expectation = "VALID";
		   System.out.println(passOrFail + "    | " + expectation + "    | " + validity + "   | " + goodQueries[i]);
		   if (!urlVal.isValidQuery(goodQueries[i])) {
			   goodCount++;
		   }
	   }
	   System.out.println("Ran " + goodQueries.length + " " + sectionName + " positive tests...");
	   if (goodCount > 0) {
		   for (int i = 0; i < goodCount; i++) {
			   System.out.print("+");
		   }
		   System.out.println(" Found " + goodCount + " positive " + sectionName + " failure(s).");
	   } else {
		   System.out.println("No positive path failure(s) found!");
	   }

	   String[] badQueries = {
			   "== 1+9x123 " ,
			   "&1x=99ba' r",
			   "=1= 2 =3",
			   "a s d f123",
			   "=1../ baz",
	   };
	   int badCount = 0;
	   for (int i = 0; i < badQueries.length; i++) {
		   String passOrFail = (!urlVal.isValidQuery(badQueries[i])) ? "PASSED" : "FAILED";
		   String validity = (urlVal.isValidQuery(badQueries[i])) ? "VALID" : "INVAL";
		   String expectation = "INVAL";
		   System.out.println(passOrFail + "    | " + expectation + "    | " + validity + "   | " + badQueries[i]);
		   if (urlVal.isValidQuery(badQueries[i])) {
			   badCount++;
		   }
	   }
	   System.out.println("Ran " + badQueries.length + " " + sectionName + " negative tests...");
	   if (badCount > 0) {
		   for (int i = 0; i < badCount; i++) {
			   System.out.print("-");
		   }
		   System.out.println(" Found " + badCount + " negative " + " " + sectionName + " failure(s).");
	   } else {
		   System.out.println("No negative path failure(s) found!");
	   }

	   int totalCount = goodCount + badCount;
	   if (totalCount > 0) {
		   System.out.println(totalCount + " " + sectionName + " failures overall.");
	   }

	   assert(totalCount == 0);

   }

   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   /*
	    *  do programming based testing. Write few unit test cases. You can have some sort of loop in
	    *  your unit test and test different URL with each instance of the loop. Something very similar to
	    *  testIsValid() but your own logic and idea. Even a single test will be sufficient if you write it like
	    *  testIsValid() method. Did you find any failures?
	    */


	   String goodSchemes[] = {
			   "http",
			   "https",
			   "ftp",
			   "HTTP",
			   "FTP",
			   "HTTPS",
			   "randomscheme"
	   };

	   String badSchemes[] = {
			   "asdffdsa",
			   "3ht",
			   "asdf",
			   "junk"

	   };

	   String allowedSchemes[] = {
			   "http",
			   "https",
			   "ftp",
			   "randomscheme"
	   };


	   String goodDomains[] = {
			   "www.google.com",
			   "www.cnn.com:80",
			   "www.asdf.biz",
			   "www.google.com:0",
			   "www.google.com:80",
			   "www.google.com:800",
			   "www.google.com:8000",
			   "www.google.com:65535",
			   "www.google.com:80",
			   "www.google.com",
			   "www.google.com",
			   "www.google.com",
			   "www.google.com/",
			   "www.google.com:80/",
			   "www.geocities.com",
			   "192.168.1.1",
			   "192.168.1.0",
			   "0.0.0.0",
			   "255.255.255.255",
			   "192.168.1.1:80",
			   "[FEDC:BA98:7654:3210:FEDC:BA98:7654:3210]:80",
		       "[1080:0:0:0:8:800:200C:417A]/",
	           "[3ffe:2a00:100:7031::1]",
	           "[1080::8:800:200C:417A]/",
	           "[2010:836B:4179::836B:4179]"
	   };

	   String badDomains[] = {
			   "asdf",
			   "junk://www.google.com",
			   "www.google.com:65536",
			   "www.google.com:65536/",
			   "www.goog le.com/?asd fdsa",
			   "192.168.1.256",
			   "192.168.256.256",
			   "256.257.258.259",
			   "256.256.256.256",
			   "192.168.1.256:80",
			   "FEDC:BA98:7654:3210:FEDC:BA98:7654:3210:80/index.html",
		       "1080:0:0:0:8:800:200C:417A/index.html",
	           "3ffe:2a00:100:7031::1",
	           "1080::8:800:200C:417A/foo",
	           "2010:836B:4179::836B:4179"
	   };

	   String[] goodPaths = {
			   "/path" ,
			   "/foo/bar",
			   "/fooo/bar/baz",
			   "/proper/commons-validator/apidocs/src-html/org/apache/commons/validator/routines/UrlValidator.html",
			   "/aburasa/CS362-004-S2018",
			   "filepath"
	   };

	   String[] badPaths = {
			   "/p ath" ,
			   "/fo :8000 o/bar",
			   "/fooo/../../index.html",
			   "/fooo/..///../bar/baz",
			   "/../baz",
			   "/ o o 0 0 0 0 ",
			   "192.168.0.0"
	   };

	   String[] goodQueries = {
			   "?asdf" ,
			   "?foo=bar",
			   "?a=1&b=2&c=3",
			   "?q=urlvalidator+apache+commons",
	   };

	   String[] badQueries = {
			   "== 1+9x123 " ,
			   "&1x=99ba' r",
			   "=1= 2 =3",
			   "a s d f123",
			   "=1../ baz",
	   };


	   System.out.println("\n\n******  TESTING ALL COMPONENTS AS URLS (RANDOMIZED TESTS) ******");
	   System.out.println("PASS/FAIL | URL");
	   System.out.println("----------------------------------------------------");

	   int i = 0;
	   Random rand = new Random();
	   UrlValidator urlVal = new UrlValidator(allowedSchemes, 0L);
	   int failCount = 0;

	   while (i < 100000) {
		   String nextTestUrl = "";

		   // randomize the validity of the inputs
		   int hasGoodSchemes = rand.nextInt(2); // randomly select 0 or 1, which is used as a boolean gate below
		   int hasGoodDomain = rand.nextInt(2); // randomly select 0 or 1, which is used as a boolean gate below
		   int hasGoodPath = rand.nextInt(2); // randomly select 0 or 1, which is used as a boolean gate below
		   int hasGoodQuery = rand.nextInt(2); // randomly select 0 or 1, which is used as a boolean gate below

		   // build out the test url
		   if (hasGoodSchemes == 1) {
			   // good
			   int index = rand.nextInt(goodSchemes.length);
			   nextTestUrl += goodSchemes[index];
		   } else {
			   // bad
			   int index = rand.nextInt(badSchemes.length);
			   nextTestUrl += badSchemes[index];
		   }

		   // in between scheme and domain, we add some required characters:
		   nextTestUrl += "://";

		   if (hasGoodDomain == 1) {
			   // good
			   int index = rand.nextInt(goodDomains.length);
			   nextTestUrl += goodDomains[index];
		   } else {
			   // bad
			   int index = rand.nextInt(badDomains.length);
			   nextTestUrl += badDomains[index];
		   }

		   // in between domain and path, we add a required character:
//		   nextTestUrl += "/";

		   if (hasGoodPath == 1) {
			   // good
			   int index = rand.nextInt(goodPaths.length);
			   nextTestUrl += goodPaths[index];
		   } else {
			   // bad
			   int index = rand.nextInt(badPaths.length);
			   nextTestUrl += badPaths[index];
		   }

		   // in between path and query, we add a required character:
		   nextTestUrl += "?";

		   if (hasGoodQuery == 1) {
			   // good
			   int index = rand.nextInt(goodQueries.length);
			   nextTestUrl += goodQueries[index];
		   } else {
			   // bad
			   int index = rand.nextInt(badQueries.length);
			   nextTestUrl += badQueries[index];
		   }

		   // after building out the whole URL, determine if it should pass or fail, and record the result:
		   if ((hasGoodDomain + hasGoodPath + hasGoodSchemes + hasGoodQuery) == 4) {
			   if (urlVal.isValid(nextTestUrl)) {
				   System.out.println("PASSED    | VALID    | VALID  | " + nextTestUrl);
			   } else {
				   failCount++;
				   System.out.println("FAILED    | VALID    | INVAL  | " + nextTestUrl);
			   }
		   } else {
			   if (!urlVal.isValid(nextTestUrl)) {
				   System.out.println("PASSED    | INVAL    | INVAL  | " + nextTestUrl);
			   } else {
				   failCount++;
				   System.out.println("FAILED    | INVAL    | VALID  | " + nextTestUrl);
			   }
		   }

		   i++;
	   }
	   assert(failCount == 0);
	   if (failCount > 0) {
		   System.out.println("There were " + failCount + " failures.");
	   } else {
		   System.out.println("There were no failures.");
	   }


   }
   
}








