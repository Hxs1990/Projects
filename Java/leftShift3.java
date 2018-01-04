public static int[] shiftLeft3(int[] numArray){
	int[] toReturn = new int[3];
	for (int i = 0; i < 3 ; ++i){
		if (i = 2) toReturn[2] = numArray[0];
		else {toReturn[i] = numArray[i+1];}
	}
	return toReturn;
}
