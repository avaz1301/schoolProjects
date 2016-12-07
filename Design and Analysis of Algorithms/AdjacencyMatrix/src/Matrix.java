
public class Matrix {
	int graph_size=0,n=0;
	Vertex[] v_array;
	
	public Matrix(int x) {
		n=x;
		graph_size=n*n;
		v_array=new Vertex[graph_size];
		int count=0;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				v_array[count++]=new Vertex(i,j);
			}//for j
		}//for i
	}//MAtrix Constructor
	
	public void printMatrix() {
		for(int i=0;i<this.graph_size;i++) {
			this.v_array[i].printVertex();
		}//for
	}//printMatrix
	
	public void generate_Graphs() {
		int a =this.n;
		int max_value= (int)Math.pow(2.0, a*a)-1;
		String temp=null;
		int count=0;
		
		for(int i=0;i<=max_value;i++) {
			temp= Integer.toBinaryString(i);
			if(temp.equals("0")) {
				System.out.print("Graph "+ (count++)+ " --> [empty set] ");
			}else {
				System.out.println("Graph "+ (count++)" -->   " + temp);
			}//else
	
			for(int j=0;j<this.graph_size;j++) {
				if(j==temp.length()) {
					break;
				}//if
				if(temp.charAt((temp.length()-1)-j)=='1') {
					this.v_array[j].printVertex();
				}//if
			}//for j
			System.out.println();
		}//for i
		
	}//generate_Graphs
	
}//Matrix


//CS323 Fall 2015 Angelo Zamudio
