class Solution {
public:
    bool isPalindrome(int x) {
        long int d=0,rev=0,z=x;
        for(int i=0;;i++) {
            d=x%10;
            rev=rev*10+d;
            x=x/10;
            if(x<=0) {
                break;
            }
            
        }if(z<0)
        {
            return false;
        }
        if(z==rev){
            return true;
        }
        else
        return false;
        
    }
};