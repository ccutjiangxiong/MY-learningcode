#codeforces.py
# -*- coding:utf-8 -*-
#爬虫需要用到的库，json用于格式转换，requests用于请求网页数据，time库用于处理时间信息（其他ppy文件中会用到）
import json, requests, time,certifi,os

# 获取contest api信息，此时reponse中已经获取到了该api提供的数据信息,此时该信息格式为json格式。
response = requests.get('https://codeforces.com/api/contest.list',verify=certifi.where())

# json数据格式转python数据格式，这样我们就可以处理获得想要的数据。
data = json.loads(response.text)

# 获取需要的result部分，这里类似于c++中的map，可以在该句代码前面输出data查看数据结构。
data = data['result']

# 将其中一些元素进行更改，变成所需要的数据格式。
for x in data:
    # print(x)
    x['start_time'] = x['startTimeSeconds']  # 转为详细时间
    x['end_time'] = x['startTimeSeconds']+x['durationSeconds']  # durationSeconds为比赛时长
    x['platform'] = 'Codeforces'  # 比赛平台
    x['contest_url'] = 'https://codeforces.com/contest/'+str(x['id'])  # 比赛链接

# python数据格式转json数据格式，方便进行存储调用
data = json.dumps(data,ensure_ascii=False)


os.makedirs('json', exist_ok=True)
f = open('json/codeforces.json', 'w', encoding='utf-8')
f.write(data)
f.close()
# print("codeforces has been completed!")
