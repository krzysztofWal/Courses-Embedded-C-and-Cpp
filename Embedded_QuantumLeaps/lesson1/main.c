int counter = 0;

int main()
{

//  int second = 0;
//  int counter  = 0;
  int *p_int;
  p_int = &counter;
  while (*p_int < 21) {
  	++counter;
//	if ((counter & 1) != 0) {
//		/* do sth when the counter is odd */
//	  second++;
//	}

	p_int = (int *)0x20000002u;
	*p_int = 0xDEADBEEF;
  }
  
  /*
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  counter++;
  */
  
  return 0;
}
