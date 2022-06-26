#include<bits/stdc++.h>
using namespace std;

class User {
        private:
        string userName;
        string userPassword;
        
        public:
        int Followers = 0;
        int Followings = 0;
        int numberOfPosts = 0;
        string bio;
        vector<string> posts;

        // constructor

        User(string name, string pass){
            userName = name;
            userPassword = pass;
                   }
        
        // setters
        void setData(string name, string pass){
            userName = name;
            userPassword = pass;
        }

        // getters
        string getPassword(){
            return userPassword;
        }
        string getUserName(){
            return userName;
        }
};

// this will store the information of all the users
map<string, string> users;
// global array to store all the users
vector<User*> UserInfo;
// maps to keep track of followers and followings
map<string, vector<User*>> followings, followers;
// this function will check that user name
// already exists or not

bool validUser(string name){
    if(users.find(name) != users.end()) return false;
    return true;
}


bool checkLogin(string name, string pass){
       if(users.find(name) != users.end() && users[name] == pass) return true;
       return false;
}

// function to print user profile
void printProfile(string userName){
       //finding user 
       int i = 0;
       
       for(; i < UserInfo.size(); i++){
            if(UserInfo[i]->getUserName() == userName) {
                break;
            }
       }
       cout<<endl;
       cout<<"**************************************"<<endl<<endl;
       cout<<userName<<endl<<endl;
       cout<<"**************************************"<<endl;

       cout<<"Posts          "<<"Followings          "<<"Followers "<<endl;
       cout<<UserInfo[i]->numberOfPosts<<setw(20)<<UserInfo[i]->Followings<<setw(19)<<UserInfo[i]->Followers<<endl;

       cout<<"-----BIO-----"<<endl;
       string printBio = UserInfo[i]->bio;
       for(char ch : printBio){
            if(ch == '*') cout<<" ";
            else cout<<ch;
       }
       cout<<endl<<endl;

}

// function to search other accounts

void searchAccounts(string userName){
       while(1){
           string searchAccount;
           cout<<"Enter Username to Search : ";
           cout<<endl;
           cin>>searchAccount;
           if(users.find(searchAccount) != users.end()){
               printProfile(searchAccount);
               cout<<"Do You Want to Follow(y/n)?"<<endl;
               char ch;
               cin>>ch;
               if(ch == 'y'){
                  for(int i = 0; i < UserInfo.size(); i++){
                      if(UserInfo[i]->getUserName() == userName){
                          UserInfo[i]->Followings++;
                          followers[searchAccount].push_back(UserInfo[i]);
                      }
                     else if(UserInfo[i]->getUserName() == searchAccount){
                          UserInfo[i]->Followers++;
                          followings[userName].push_back(UserInfo[i]);
                      }
                  }
               }
           }
           else {
               cout<<"Sorry! User Not Found!!!"<<endl;
           }

           cout<<"Want to Search More Users(y/n)?"<<endl;
           char ch;
           cin>>ch;
           if(ch == 'y') continue;
           else break;
       }
       return;
}

// function to check followings

void checkFollowings(string userName){
       cout<<"*******List Of Followings*******"<<endl;
       for(int i = 0; i < followings[userName].size(); i++){
           cout<<followings[userName][i]->getUserName()<<endl;
       }
       return;
}

// function to check followers

void checkFollowers(string userName){
       cout<<"*******List Of Followers*******"<<endl;
       for(int i = 0; i < followers[userName].size(); i++){
           cout<<followers[userName][i]->getUserName()<<endl;
       }
       return;
}

// function to check posts

void checkPosts(string userName){
       cout<<"*******List Of Followings*******"<<endl;
       for(int i = 0; i < followings[userName].size(); i++){
           cout<<followings[userName][i]->getUserName()<<endl;
       }
       while(1){
       cout<<"Select User to check Posts : "<<endl;
       string checkUserPost;
       cin>>checkUserPost;
       int i = 0;
       for(; i < UserInfo.size(); i++){
           if(UserInfo[i]->getUserName() == checkUserPost) break;
       }

       cout<<"This User has posted "<<UserInfo[i]->posts.size()<<" posts"<<endl;
       cout<<"Enter the number of Posts you want to see : "<<endl;
       int numPost;
       cin>>numPost;

       int oldNew;
       cout<<"1)Check Recent Posts\n2)Check Oldest Post"<<endl;
       cin>>oldNew;
       int n = UserInfo[i]->posts.size();
       if(oldNew == 1){
            cout<<"Posts of "<<UserInfo[i]->getUserName()<<" :"<<endl;
            for(int j = n - 1 ; j >= n - numPost; j--){
                string post = UserInfo[i]->posts[j];
                for(char ch : post){
                    if(ch == '*') cout<<" ";
                    else cout<<ch;
                }
                cout<<endl;
            }
       }
       else {
            cout<<"Posts of "<<UserInfo[i]->getUserName()<<" :"<<endl;
            for(int j = 0 ; j < numPost; j++){
                 string post = UserInfo[i]->posts[j];
                for(char ch : post){
                    if(ch == '*') cout<<" ";
                    else cout<<ch;
                }
                cout<<endl;
            }  
       }

       char op;
       cout<<"Want to See more Posts(y/n)?"<<endl;
       cin>>op;

       if(op == 'y') continue;
       else break;

       }

       return ;
}

// function to create Posts
void createPosts(string userName){
       int i = 0;
       for(; i < UserInfo.size(); i++){
           if(UserInfo[i]->getUserName() == userName) break;
       }

       while(1){
       cout<<"Write a Post :"<<endl;
       string post;
       cin>>post;
       UserInfo[i]->posts.push_back(post);
       UserInfo[i]->numberOfPosts++;
       cout<<"Post Has Been Created Successfully!!!"<<endl;
       cout<<"Want to create more Posts(y/n)?"<<endl;
       char op;
       cin>>op;

       if(op == 'y'){
          continue;
       }
       else break;
       }
}

void deleteAccount(string userName) {
      users.erase(userName);
      
      for(User *u : followings[userName]){
        u->Followers--;
        string currentUser = u->getUserName();
        for(int i = 0; i < followers[currentUser].size(); i++){
            if(followers[currentUser][i]->getUserName() == userName) {
                followers[currentUser].erase(followers[currentUser].begin() + i);
                break;
            }
        }
      }

      for(User* u : followers[userName]){
        u->Followings--;
        string currentUser = u->getUserName();
        for(int i = 0; i < followings[currentUser].size(); i++){
            if(followings[currentUser][i]->getUserName() == userName) {
                followings[currentUser].erase(followings[currentUser].begin() + i);
                break;
            }
        }
      }

      followers.erase(userName);
      followings.erase(userName);

      int i = 0;
      for(; i < UserInfo.size(); i++){
        if(UserInfo[i]->getUserName() == userName) break;
      }

      UserInfo.erase(UserInfo.begin() + i);

      cout<<"Your Account Deleted Successfully!!!"<<endl;
      return;     
}

void editProfile(string userName){
      int i = 0;
      for(; i < UserInfo.size(); i++){
        if(UserInfo[i]->getUserName() == userName) break;
      }
      while(1){
      cout<<"***Edit Your Profile***"<<endl;
      cout<<"1)Edit UserName\n2)Edit Password\n3)Edit bio\n4)Exit"<<endl;
      int choice;
      cout<<"Enter a choice : "<<endl;
      cin>>choice;

      if(choice == 1){
       string newName;
       cout<<"Enter a New UserName : "<<endl;
       cin>>newName;
       if(!validUser(newName)){
        cout<<"This Username is already existed!!! Try different Username!!!"<<endl;
        continue;
       }

       else {
          users.erase(userName);
          UserInfo[i]->setData(newName, UserInfo[i]->getPassword());
          users[newName] = UserInfo[i]->getPassword(); 
          cout<<"Update Done Successfully!!!"<<endl;        
       }
      }

      else if(choice == 2){
       string newPass;
       cout<<"Enter a New Password : "<<endl;
       cin>>newPass;
       UserInfo[i]->setData(userName, newPass);
       users[userName] = newPass;
       cout<<"Update Done Successfully!!!"<<endl; 
      }

      else if(choice == 3){
          string newBio;
          cout<<"Enter a new Bio : "<<endl;
          cin>>newBio;
          UserInfo[i]->bio = newBio;
          cout<<"Update Done Successfully!!!"<<endl; 
      }

      else break;

      }

      return;     
}

void loginPage(string userName){
     cout<<"--------------------------------------------------"<<endl;
     cout<<"|                                                |"<<endl;
     cout<<"|                  Your Profile                  |"<<endl;
     cout<<"|                                                |"<<endl;
     cout<<"--------------------------------------------------"<<endl;
     printProfile(userName);

     while(1){
         cout<<"1)Edit Profile\n2)Search Accounts\n3)Check Followings\n4)Check Followers\n5)Check Posts\n6)Create Post\n7)Delete Account\n8)logout"<<endl;
         cout<<"Enter a Choice : "<<endl;
         int choice;
         cin>>choice;

         if(choice == 1){
            editProfile(userName);
         }
   
         if(choice == 2){
             searchAccounts(userName);
         }

         else if(choice == 3){
             checkFollowings(userName);
         }

         else if(choice == 4){
              checkFollowers(userName);
         }

         else if(choice == 5){
               checkPosts(userName);
         }

         else if(choice == 6) {
               createPosts(userName);
         }

         else if(choice == 7) {
               deleteAccount(userName);
         }

         else {
             cout<<"Logging Out..."<<endl;
             break;
         }
     }

     return;
}

int main(){
     cout<<"--------------------------------------------------"<<endl;
     cout<<"|                                                |"<<endl;
     cout<<"|       WELCOME TO TWITTER-LITE APPLICAITON      |"<<endl;
     cout<<"|                                                |"<<endl;
     cout<<"--------------------------------------------------"<<endl;
     while(1){
           int choice;
           cout<<"1)Sign-Up\n2)Log-in\n3)Exit"<<endl;
           cout<<"Enter a choice : "<<endl;
           cin>>choice;
           if(choice == 1){
               string tmpUserName, tmpUserPass;
               cout<<"Enter User Name : "<<endl;
               cin>>tmpUserName;
               if(!validUser(tmpUserName)) {
                   cout<<"User Name already Exists!!!"<<endl;
                   cout<<"Try with different User Name"<<endl;
                   continue;
               }
               cout<<"Enter User Password : \n";
               cin>>tmpUserPass;
        
               // creating user
               User *tmpUser = new User(tmpUserName, tmpUserPass);
               users[tmpUserName] = tmpUserPass;
               string tmpBio;
               cout<<"Describe who you are with your BIO : "<<endl;
               cout<<"Enter a Bio : "<<endl;
               cin>>tmpBio;
               tmpUser->bio = tmpBio;
               UserInfo.push_back(tmpUser);
               cout<<"size = "<<UserInfo.size()<<endl;
               cout<<"Congratulations!!! Your Account Has Been Created Successfully!!!"<<endl;
               loginPage(tmpUserName);
           }

           else if(choice == 2) {
                     string logInName;
                     string logInPass;
                     cout<<"Enter User name : ";
                     cin>>logInName;
                     cout<<endl;
                     cout<<"Enter User password : ";
                     cin>>logInPass;
                     cout<<endl;

                     if(checkLogin(logInName, logInPass)){
                         cout<<"Login Successfull!!!"<<endl;
                         loginPage(logInName);
                     }

                     else {
                         cout<<"Either your Username or your Password is not correct! Try Again!"<<endl;
                         continue;
                     }
           }

           else {
               cout<<"Exiting..."<<endl;
               break;
           }

     }
    return 0;
}