class TileDBRead{

	public native void display();
 	public static void main(String[] args){
		TileDBRead read = new TileDBRead();
		read.display();
	}

	static{
		System.loadLibrary("TileDBRead");
	}
}
