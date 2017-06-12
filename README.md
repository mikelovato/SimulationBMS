# SimulationBMS
This is the BUPT computer science data structure curriculum design, using C++ language to build a library management system
                                
 ### Library management system manual


The system is for administrators, students, teachers, three major users. Students and teachers have different access to books, administrators
In addition to the functions of students and teachers, books and information and user information in the library should be maintained and modified to make sure
Ensure the normal use of the system.


Click librarry.exe to jump out of the library login screen, click the login button and fill in your username and password,
The system will automatically determine whether the current login is a regular user (student or teacher) or administrator and jump out of the different bounds
Noodles.

1. common user interface
The average user has the ability to borrow books, return books, make appointments, check personal information, and modify personal information.


    (1) borrow books
Click the interface library button, enter the number of books you want to borrow, and the number of days you want to borrow ID. Click OK if you enter
The correct ID and the book have not yet been lent. Enter a valid library time and you can borrow it successfully. Otherwise prompt
Checking information.


    (2) return the book
Click the interface, return the book button, enter the ID you want to return the book, and if the book lending information in conformity with the tips
Return the book successfully, otherwise prompt to check enter ID.

    
(3) reservation
Click the interface appointment button to enter the ID of the book you want to book, if the book is not in the library and the borrower does not
The current user (the user cannot book and borrow the same book at the same time) prompts the appointment to succeed, otherwise it will not be able to make an appointment
The current status of the book you will book when you log in next time.


    (4) check personal information
Click on the personal information button to view your information, including the name, ID, Institute, integrity status,
Status, account balance, account creation time, number of books and their ID, amount of appointment and their ID.

    
(5) modify personal information
Click on the modified information, you can modify personal information, you can modify the name, college, ID, password. Other
Some attributes can not be modified at will.


2. administrator interface
Administrators have access to books, books, books, books, books, changes in accounts, accounts
Information, account recharge, this month's information statistics, the function of creating new accounts.


    (1) borrow books
Click on the library button to borrow books. Unlike regular users, administrators need to enter user ID to borrow books,
That is, administrators can borrow books from other users.

    
(2) return the book
And ordinary users also books, enter the book ID to return, the system automatically detects who borrowed.

    
(3) modify book information
Click Modify the book button, enter the book to modify the ID, modify the book.

    
(4) purchase of books
Click on the Add button to fill in the type, title, author, number, publisher, price, and permissions for the book
And other information, buy books.

    
(5) delete books
Click the delete Book button, enter the book ID, delete the book


    (6) modifying user information
Enter the user ID to modify the user information.


    (7) display account information
Click the display account information button to display information for all users. You can search user information by entering ID.


    (8) recharge account
Enter the user ID and recharge the amount to recharge.


    (9) statistics this month
Click the statistics button this month to display all the information for that month.

    
(10) creating accounts


   本系统面向管理员，学生，教师三大用户。学生和教师有不同的图书借阅权限，管理员除了具有学生和教师的功能外，还要对馆内的图书信息和用户信息等进行维护和修改，以确保该系统的正常使用。
   点击librarry.exe跳出图书馆登录界面，点击登录按钮填入自己的用户名和密码登录，系统会自动判断当前的登录者是普通用户（学生和教师）还是管理员，据此跳出不同的主界面。

    
    1. 普通用户界面

         普通用户具有借书，还书，预约，查看个人信息，修改个人信息的功能。
    
        （1）.借书
            
              点击界面借书按钮，输入你想借的书的ID和借书的天数，点击确定，如果输入
          
          正确的ID以及该书还没有被借走，输入有效的借书时间，就可借阅成功。否则提示

          检查信息。

        （2）.还书
 
              点击界面还书按钮，输入你要还的书的ID，如果与该书的借阅信息吻合，提示

          还书成功，否则提示检查输入ID。        

        （3）.预约

              点击界面预约按钮，输入你想要预约的书的ID，如果该书不在馆内且借书人不

          当前用户（用户不能同时预约和借阅同一本书），提示预约成功，否则提示无法预约

          下次登录时会提示你预约的书的当前状态。

        （4）.查看个人信息

              点击个人信息按钮，查看自己的信息，这些信息包括姓名，ID，学院，诚信状况，

          身份，账户余额，账户创建时间，借书数量及其ID，预约数量及其ID。

        （5）.修改个人信息

              点击修改信息可以对个人信息进行修改，可以修改姓名，学院，ID，密码。其他

          的一些属性不能随意修改。               
            
        
    
    2. 管理员界面

       管理员具有借书，还书，修改图书信息，购入图书，删除图书，更改账户信息，显示账户

    信息，账户充值，本月信息统计，创建新账户的功能。

         （1）.借书

              点击借书按钮进行借书，与普通用户不同的是，管理员需要输入用户ID进行借书，

          也就是管理员可以给别的用户借书。

         （2）.还书

              与普通用户还书一样，输入书ID来还，系统自动检测是谁借的。

         （3）.修改图书信息

              点击修改图书按钮，输入要修改的书的ID，对书进行修改。

         （4）.购入图书

              点击增加图书按钮，填写书类型，书名，作者，数量，出版社，价格，借阅权限

          等信息，购入图书。

         （5）.删除图书

              点击删除图书按钮，输入书ID删除该书

         （6）.修改用户信息
 
              输入用户ID对该用户信息进行修改。

         （7）.显示账户信息

              单击显示账户信息按钮，显示所有用户的信息，可以通过输入ID搜索用户信息。

         （8）.充值账户

              输入用户ID和充值金额进行充值。

         （9）.本月统计

              单击本月统计按钮，显示当月的所有信息。

          （10）.创建账户
  
