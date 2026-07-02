/*============================================================================

Assignment: pa02 - Encrypting a plaintext file using the Hill cipher

Author: Michael Wang (mi993440)
Language: java
To Compile: 
javac pa02.java
To Execute: java pa02.java kX.txt pX.txt
where kX.txt is the keytext file
and pX.txt is plaintext file
All input files are simple 8 bit ASCII input
All execute commands above have been tested on Eustis
Class: CIS3360- Security in Computing- Summer 2025
Instructor: McAlpin
Due Date: per assignment
+===========================================================================
*/

package pa02;

import java.util.*;
import java.io.*;
import java.lang.Math;

public class pa02 {

	public static void main(String[] args) {
		
		//
		//	Input Processing
		//
		
		//	Command line arguments:
		String cipherFilename = "";
		String textFilename = "";
		try {
			cipherFilename = args[0];
			textFilename = args[1];
		}
		//	Catch for incorrect number of arguments used.
		catch(IndexOutOfBoundsException e)
		{
			System.out.println("Wrong number of arguments.");
			e.printStackTrace();
		}
		
		
		//	Variables for file reading
		File cipherFile = new File(cipherFilename);
		File textFile = new File(textFilename);
		Scanner cipherScanner;
		BufferedReader textReader;
		
		int matSize = 0;
		int[][] matrix = {{0},{0}};
		ArrayList<Character> text = null;
		
		
		//	Handle file reading exceptions.
		try 
		{
			//	Read cipher matrix
			cipherScanner = new Scanner(cipherFile);
			matSize = cipherScanner.nextInt();
			matrix = new int[matSize][matSize];
			for(int i = 0; i < matSize; i++)
			{
				for(int j = 0; j < matSize; j++)
				{
					matrix[i][j] = cipherScanner.nextInt();
				}
			}
			cipherScanner.close();
			
			//	Read plain text
			
			textReader = new BufferedReader(new FileReader(textFile));
			text = new ArrayList<Character>();
			int nextChar;	//	Var to hold next char in file.
			while(-1 != (nextChar=textReader.read()))
			{
				//	Add char to plaintext array if it is a letter. Ensure lowercase.
				if(Character.isLetter(nextChar))
					text.add(Character.toLowerCase((char)nextChar));
			}
			
			// Ensure correct padding
			int numPad = matSize-(text.size() % matSize);
			if(numPad == matSize) numPad = 0;
			for(int i = 0; i < numPad; i++)
				text.add('x');
			
		}
		//	Exception handling
		catch(FileNotFoundException e)
		{
			System.out.println("File not found.");
			e.printStackTrace();	
		} 
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		
		//
		//	Output 1
		//
		
		System.out.println("Key matrix:");
		for(int i = 0; i < matSize; i++)
		{
			for(int j = 0; j < matSize; j++)
			{
				System.out.printf("%4d",matrix[i][j]);
				
			}
			System.out.println();
		}
		
		System.out.println("\nPlaintext:");
		for(int i = 0; i < text.size(); i++)
		{
			System.out.print(text.get(i));
			if(i != 0 && i % 80 == 0) System.out.println();
		}
		
		//
		//	Hill Cipher Encryption
		//
		
		//	Process plaintext
		ArrayList<Integer> nums = new ArrayList<Integer>();
		for(int i = 0; i < text.size(); i++)
		{
			//	Convert array values to each letter's index in alphabet
			//	a = 0, z = 25
			nums.add(i,(text.get(i)-97));
		}
		
		//	Encryption
		ArrayList<Character> encrypted = new ArrayList<Character>();	// Holds final encrypted text
		int[] multiplicand = new int[matSize];			// Multiplicand matrix
		int[] product = new int[matSize];		// Product matrix
		//	Matrix multiplication
		for(int i = 0; i < nums.size(); i+=matSize)
		{
			for(int j = 0; j < matSize; j++)
			{
				multiplicand[j] = nums.get(i+j);
			}
			
			for(int j = 0; j < matSize; j++)
			{
				product[j] = 0;
				for(int k = 0; k < matSize; k++)
				{
					product[j] += matrix[j][k] * multiplicand[k];
				}
			}
			
			for(int j = 0; j < matSize; j++)
			{	
				//	Convert back to ASCII before adding to final list.
				encrypted.add((char)((product[j] % 26) + 97));
			}
		}
		
		//
		//	Output 2
		//
		
		System.out.println("\n\nCiphertext:");
		for(int i = 0; i < encrypted.size(); i++)
		{
			System.out.print(encrypted.get(i));
			if(i != 0 && i % 80 == 0) System.out.println();
		}

	}
}

/*=============================================================================
| I, Michael Wang (mi993440) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================
*/

