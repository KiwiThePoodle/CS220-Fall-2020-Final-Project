bool SkipBoGame::play(int p){
   bool move = true;
   while (move){
     std::cout << "(m)ove [start] [end] or (d)raw ? ";
     std::string action;
     std::string from;
     std::string to;

     std::cin >> action;
     std::cin >> from;
     std::cin>>to;   //depending on user input (move) checks validity
     while ((from == "0" && (to == "1" || to == "2" || to == "3" || to == "4")) || (action!= "m" && action != "d") || (from != "0" && from != "1" && from != "2" && from != "3" && from != "4" && from != "5" && from != "6" && from != "7" && from != "8" && from != "9")  ||(to != "a" && to != "b" && to != "c" && to != "d" && to != "1" && to != "2" && to != "3" && to != "4" )){
       illegalMove();
       std::cin >> action;
       std::cin >> from;
       std::cin >> to;
     }
	
     std::cout << std::endl;

     int f;
     int t;
     int b;
  
     if (action != "d"){   //just converts from letter to number for easier usage
       f = std::stoi(from);
       if (to == "a" || to == "b" || to == "c" || to == "d"){
	        if (to == "a"){b = 0;}
	        if (to == "b"){b = 1;}
	        if (to == "c"){b = 2;}
	        if (to == "d"){b = 3;}
	            t = 100;
          }else{
	            t = std::stoi(to);  
          }
       }
    if (action == "d"){   //checks if player can draw, then draws if player's hand size is zero
    //draw
       if (peep[p]->handSize() == 0){
	        for (int i = 0; i < 5; i ++){
	            peep[p]->drawToHand();
	        }
       }
    }
     
     if (action == "m"){
     
      int leave;
      int target;
       
      if (f == 0){
        leave = peep[p]->getStockCardValue();
      }
      if (f >= 1 && f <= 4){
        leave = peep[p]->getDiscardCardValue(f);
      }
      if (f >= 5 && f <= 9){
        leave = getHandCardValue(f);
      }
       
      if (t == 100){
        if (build[b]->size()==0){
          target = 0;
        }else{
          target = build[b]->topCardValue();
        }
      }
       
      if (t >= 1 && t <=4){
        target = getDiscardCardValue(t);
      }
       
      if (leave > target + 1 || leave == 0){
        move = true;
        
        
        
      }else{
        move = false;
        illegalMove();
      }
      
       
     }
    
     
     
     
     
     
   if (move == true){
	    if (t <= 4 && t >= 1){
	        peep[p]->handToDiscard(c, t);
	   
	        return true;
	    }
   }
   if(move) {
	    build[b]->addCard(c);
   }
    
   move = !move;
     
   }
   
   return false;
}
