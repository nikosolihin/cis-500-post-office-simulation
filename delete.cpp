if ( isAvailable && postOffice.isEmpty != false ) {
    postOffice.dequeue(currentArrivalTime);
    
    // generate random serving time for clerk
    servingTime = (rand() % 4) + 1;
    
    isAvailable = false;
}
            
            // enqueue a customer after certain minutes have passed
 if ( currentMin % arrivalTime == 0 ) {
     postOffice.enqueue(arrivalTime);
     totalCustomers++;
 }

            // serve the customer if clerk is not busy
    if ( isAvailable == true && postOffice.isEmpty() == false) { 
     postOffice.dequeue();
                isAvailable = false;
     // tellArray[i].time_At = servingTime;                      
    }

            //Decrement time spent at teller    
 if ( isAvailable == false) {
     servingTime --;
 }
 
 //Set teller to open if time limit is reached
 if ( servingTime == 0 ) {
     isAvailable = true; 
 }

 wait_Time += bankQ.getSize(); //Set wait time to persons left in queue
 
 

