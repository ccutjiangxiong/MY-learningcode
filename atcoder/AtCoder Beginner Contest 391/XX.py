s=input("用户名: ") 

p=input("密码: ") 

print("登录成功") 

print("       #1.添加会员信息") 

print("       #2.删除会员信息") 

print("       #3.修改会员信息") 

print(" #4.查看会员信息") 

print("       #5.退出系统") 

mp={} 
while True: 
    num=int(input("请输入选择: ")) 
    if num==1: 
        u=input("请输入增加的会员名称: ") 
        v=input("请输入增加的"+u+"密码: ") 
        print(u+"会员增加成功")

        mp[u]=v 

    elif num==2: 

        u=input("请输入删除的会员信息: ") 

        mp.pop(u) 

        print(u+"会员删除成功") 

    elif num==3: 
        u=input("请输入要修改的会员信息: ") 
        mp.pop(u) 
        u=input("请输入要修改的会员的姓名: ") 
        v=input("请输入要修改的会员的密码: ") 
        mp[u]=v 
        print(u+"会员修改成功") 
    elif num==4: 
        for [u,v] in mp.items(): 
            print("当前会员用户为: "+u) 

            print("当前会员密码为: "+v) 

    elif num==5: 
        print("退出系统") 
        break 
    else: 
        print("输入错误，请重新输入！") 