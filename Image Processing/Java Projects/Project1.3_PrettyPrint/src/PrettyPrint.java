import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

public class PrettyPrint {
    public static void prettyPrint(Scanner input, PrintWriter writer) {
        int numRows = input.nextInt();
        int numCols = input.nextInt();
        input.nextInt();
        input.nextInt();
        int temp = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                temp = input.nextInt();
                if(temp > 0){
                    writer.print(temp+" ");
                }else{
                    writer.print("  ");
                }
            }//for j
            writer.println();
        }//for i
    }

    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 1) {
            System.out.println("Please Provide an input.");
            return;
        }
        String output_file = args[0];
        output_file = output_file.substring(0, output_file.lastIndexOf("."))+"_PP.txt";

        Scanner input = new Scanner(new File(args[0]));
        PrintWriter out_write = new PrintWriter(output_file);

        prettyPrint(input, out_write);

        input.close();
        out_write.close();
    }//main
}

//Angelo Zamudio CS381 Fall 16'