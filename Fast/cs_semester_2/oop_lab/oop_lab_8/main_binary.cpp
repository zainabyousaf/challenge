#include <math.h> // only for pow
#include <iostream>
using namespace std;
void toBinary(int *&array,int &size, int n){
  // convert decimal to bin
  int number = n;
  size=0;
  while(n/2 >0) {n=n/2; size++;}
  size++;
  array = new int [size];
  for(int i=0; i < size; i++) {array[i] = number %2; number= number/2;}
}
int toDecimal(int *array, int size){
  // from binary to decimal
  int sum=0;
  for(int i=0; i < size; i++) sum=sum + pow(2,i)*array[size-i-1];
  return sum;
}
class BinaryNum
{
private:
  int* binNum;	//integer array to save binary number
  int noOfBits;	//total no. of bits
public:
  //*modified
  BinaryNum(){binNum=0; noOfBits=0;}
  
  BinaryNum(const char *str){
    int lenth=0;
    noOfBits=0;
    while(*(str+lenth++)) noOfBits++;
    
    binNum = new int [noOfBits];
    //cout << noOfBits << "---------------\n";
    for(int i=0; i < noOfBits; i++) binNum[i] = str[noOfBits-i-1]-'0';
  }
  //------------------- get number of bits
  int getNumberOfBits() {return noOfBits;}
  int * getBinaryNo() {return binNum;}
  
  BinaryNum operator + (const BinaryNum & obj){
    int sum = toDecimal(obj.binNum,obj.noOfBits)+toDecimal(this->binNum,this->noOfBits);
    cout << toDecimal(obj.binNum,obj.noOfBits) << endl;
    cout << toDecimal(this->binNum,this->noOfBits) << endl;
    //cout << "*************** sum ***** " << sum << endl;
    BinaryNum temp;
    toBinary(temp.binNum, temp.noOfBits,sum);
    return temp;
  }

  //---------------------------------- - operator

  BinaryNum operator - (BinaryNum &rhs){
    int result = toDecimal(this->binNum,this->noOfBits) - toDecimal(rhs.binNum,rhs.noOfBits);
    if(result < 0){
      result = result*-1; // making positve to avoid erro
    }
    BinaryNum temp;
    toBinary(temp.binNum,temp.noOfBits,result);
    return temp;
  }
  /*
  BinaryNum operator + (const BinaryNum & obj){
    BinaryNum *temp = new BinaryNum;
    //BinaryNum temp = new BinaryNum;
    int max = (this->noOfBits > obj.noOfBits)? this->noOfBits : obj.noOfBits;
    temp->binNum= new int [max + 1];
    //temp.binNum= new int [noOfBits+1];
   
  int carry =0;
  int index =0;
  int result;
  while(index < this->noOfBits && index < obj.noOfBits){
    result = this->binNum[index] + obj.binNum[index]+carry;
    if(result ==3){
      carry =1;
      result =1;
    }
    else if (result == 2){carry=1; result = 0;}
    else{
      carry=0;
    }
    //cout << "*"<< result;
    temp->binNum[index] = result;
    index++;
    //cout << result << "#";
  }
  //cout<< index << "*************"; 
  if(this->noOfBits > obj.noOfBits){
    for(int i=index; i< this->noOfBits; i++){
      result = this->binNum[i]+carry;
      if(result == 3){carry=1; result = 1;}
      else if(result ==2){carry=1; result=0;}
      else{carry=0;}
      temp->binNum[index++] = result;
      //   cout << "*"<< result; 
    }
  }
  else{
    //cout << "#############################3";
    for(int i=index; i< obj.noOfBits; i++){
      result = obj.binNum[i]+carry;
      //      cout << result;
      if(result == 3){carry=1; result = 1;}
      else if(result ==2){carry=1; result=0;}
      else{carry=0;}
      temp->binNum[index++] = result;
      //cout << result;
    }
  }
  
  if(carry==1){temp->binNum[index++]=1;temp->noOfBits=index;}
  else{temp->noOfBits = index;}
//if(carry ==1) {temp->binNum[index]=1;temp->noOfBits=index;}
  //else{temp->noOfBits=index-1;}
  //int *inverted = new int [index];
  //for(int i=0; i < temp->noOfBits; i++) inverted[i]=temp->binNum[temp->noOfBits-i-1];
  //delete []temp->binNum;
  //temp->binNum = inverted;
  //  delete []this->binNum;
  //cout << "----------" << temp->noOfBits << endl;
  return *temp;
}
  */

  //------------------------------------ = operator
  int &operator [](int val){
    if(this->noOfBits > val)
    return this->binNum[val];
    else if(this->noOfBits == val){
      int *temp = new int [this->noOfBits+1];
      for(int i=0; i< this->noOfBits; i++) temp[i]=this->binNum[i];
      delete []this->binNum;
      this->binNum=temp;
      this->noOfBits=this->noOfBits+1;
      return this->binNum[val];
    }
    else {return this->binNum[0];}
  }

  //----------------------------------- A - B
  /*
  BinaryNum operator - (const BinaryNum &rhs){
    BinaryNum temp;
    // first take 2's complement and then add
    int result =0, carry=0, index=0;
    if(this->noOfBits > rhs.noOfBits){
      temp.binNum = new int [this->noOfBits];
    while(index < this->noOfBits && index < rhs.noOfBits){
      if(this->binNum[index]==0){
	result = carry + this->binNum[index]-rhs.binNum[index];
      }
      else{
	result = this->binNum[index]-rhs.binNum[index];
	carry=0;
      }
      
      if(result == -1){carry =1; result=1;}
      temp.binNum[index++] = result;
    }
    for(int i=index; i < this->noOfBits; i++){
      if(carry ==1 && this->binNum[i]==1){
	result = this->binNum[i]-carry;
	carry=0;
	
      }
      temp.binNum[index++]=result;
    }
    }
    //-------------------------------- else minuhend is greater
    else{
      temp.binNum = new int [rhs.noOfBits];
       while(index < this->noOfBits && index < rhs.noOfBits){
	 if(rhs.binNum[index]==0){
	result = carry + rhs.binNum[index]-rhs.binNum[index];
      }
      else{
	result = rhs.binNum[index]-rhs.binNum[index];
	carry=0;
      }
      
      if(result == -1){carry =1; result=1;}
      temp.binNum[index++] = result;
      //index++;
    }
    for(int i=index; i < rhs.noOfBits; i++){
      if(carry ==1 && rhs.binNum[i]==1){
	result = rhs.binNum[i]-carry;
	carry=0;
	
      }
      temp.binNum[index++]=result;
    }
    }
    temp.noOfBits = index;
    return temp;
  }
  */

  bool operator ==(const BinaryNum &rhs){
    int left=toDecimal(this->binNum, this->noOfBits);
    int right=toDecimal(rhs.binNum, rhs.noOfBits);
    if( left == right ) {return true;}
    return false;
  }
//--------end of modified
  void Print(){
	  if(binNum != 0){
	    for(int i = 0 ; i< noOfBits ; i++)
	      cout<<binNum[i];
	  }
	  //out<<endl;
	}
  //--------------- << operator
   friend ostream & operator << (ostream &out, const BinaryNum & obj){
     for(int i = 0 ; i< obj.noOfBits; i++){
      out << obj.binNum[obj.noOfBits-i-1];
	  }
	  out << endl;
    return out;
}
  //--------------- >> 
istream &operator >>(istream &in){
  char buffer[50];
  in >> buffer;
  int size=0;
  while(buffer[size++] == '\0');
  if(this->noOfBits !=0) this->noOfBits= size-1;
  this->binNum = new int [this->noOfBits];
  for(int i=0; i< this->noOfBits; i++) this->binNum[i] = buffer[i]-'0';
    }
  
  ~BinaryNum(){
    if(noOfBits !=0) delete []this->binNum;
    binNum = 0; // or nullptrx
  }

};


int main()
{
  

  BinaryNum b1;			//noOfBits = 0, binNum is NULL
  BinaryNum b2("1111");	//noOfBits = 3, binNum is {1,0,1}
  BinaryNum b3("1111");	//noOfBits = 4, binNum is {1,0,0,

  cout << (b3+b2);
  cout << (b2-b3);
  cout << (b2 == b3);

  return 0;
}
