//lesson three
int counter;

int main() {
  
    /* lesson one
    unsigned int counter = 0;
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
    counter++;
    counter++;
    */
  
    /* lesson two
    int counter = 0;
   
    while (counter < 21)
    {
        counter++;
        if ((counter & 1) != 0)
        {
          // do sth when the counter is odd 
        
        }
        else
        {
          // do something when the counter is odd 
        }
    }
     */
    
  
    // lesson three
    int *p_int;
    p_int = &counter; // store adress of counter in the pointer
    
    while (*p_int < 21)
    {
        (*p_int)++;
    }
    
    p_int = (int*)0x20000002u;
    *p_int = 0xDEADBEEF;
    
    
    return 0;
}

