import java.io.*;
import java.util.Scanner;
/**
 * 
 * @author Angelo Zamudio CS323 Fall 15'
 *  Takes a specified (.txt) file. Reads in regular expressions line by line and separates it into its groups
 *  by keeping track of corresponding pairs of open/close parentheses and writes them to an output (.txt) file.
 *  It accomplishes this using a brute force method that reads in a regex and goes through it each character 
 *  looking for an open parentheses. It then runs through the remaining characters adding 1 to a counter for every open parentheses
 *  and subtracting 1 for every close parentheses until counter reaches zero, at which point the program has found the matching close parentheses.
 *  The location of matching parentheses gives us the sub-string/sub-group.     <OUTPUTS TO CONSOLE AND OUTPUT FILE>
 *
 */
public class grouper {
	public static void main(String args[]) throws IOException {
		String line=null;
		Scanner in_file= new Scanner (new File(args[0])); // FOR CMD
		Writer it_writes = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("groupsOutput.txt"), "utf-8"));
		///////////////////////////////////////////////////////////
		while(in_file.hasNext()) {
			line=in_file.nextLine();
			if(!line.isEmpty()) {
				grouping(it_writes, line);
			}//if
		}//while file.hasNext()
		///////////////////////////////////////////////////////////
		in_file.close();
		it_writes.close();
	}//main
	
	private static void grouping(Writer it_writes, String regex) throws IOException {
		int grp_start_index=0, grp_count=0, i=0;
		String[] groups= new String[15];
		 if(regex.charAt(0)=='(' && regex.charAt(regex.length()-1)!=')'){	
				groups[grp_count++]=regex;
		}
		if(regex.charAt(0)!='(') {
			groups[grp_count++]=regex;
		}
		//////////////////////////////////////////////////////////////////////////////////
		while(i<regex.length()) {
			int paren_match=1;
			if(regex.charAt(i)=='(') {
				grp_start_index=i;
				//////////////////////////////////////////////////////////////////
				for(int j=grp_start_index+1;j<regex.length();j++) {
					if(regex.charAt(j)==')') {
						paren_match-=1;
						if(paren_match==0) {
							groups[grp_count++]=regex.substring(grp_start_index, j+1);
							break;
						}
						if(paren_match<0) {
							System.out.println("Uneven # of Open/Close parentheses.");
							break;
						}//iff break				
					}//char at j	
					else if(regex.charAt(j)=='(') {
						paren_match+=1;
					}//else if
				}//for
				/////////////////////////////////////////////////////////////////////
			}//if
			i++;
		}//while
		/////////////////////////////////////////////////////////////////////////////////////
		outputFile(it_writes,groups);		
	}//grouping
	
	private static void outputFile(Writer it_writes, String[] tofile)  throws IOException{
		it_writes.write("Inputted Text:  " +tofile[0]+"\r\n");
		for(int i=0;i<tofile.length;i++) {
			if(tofile[i]!=null) {
				it_writes.write("Group " +i+ "--->  " +tofile[i] +"\r\n");
			}//if
		}//for
		it_writes.write("\r\n");
		it_writes.flush();		
	}//outputFile
	
}//grouper

// CS323 Fall 2015 Angelo Zamudio

