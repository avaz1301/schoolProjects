
public class Vertex {
		int x=0,y=0;
		public Vertex() {
			x=0;
			y=0;
		}//Constructor
		
		public Vertex(int a, int b) {
			x=a;
			y=b;
		}//Constructor
		
		public int getX() {
			return x;
		}//getX
		
		public int getY() {
			return y;
		}//getY
		
		public void printVertex() {
			System.out.print("("+this.x+","+this.y+")  ");
		}//printVertex
		
}//Vertex

//CS323 Fall 2015 Angelo Zamudio
