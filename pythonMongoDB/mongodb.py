import pymongo


#mongo db세팅후에, 변경해서 사용할 것
conn = pymongo.MongoClient("mongodb+srv://nicecapj:epdlxjqpdltm82!@testcluster-tncwx.gcp.mongodb.net/test?retryWrites=true&w=majority")
#conn = pymongo.MongoClient(host='172.19.151.92', port=27017, username="nicecapj", password="epdlxjqpdltm82!")
print(conn)
print(" ")
db = conn.get_database('test')	#데이터 베이스 선택(mongodb.com은 무료는 1개만 됨.)
if not db:
	db = conn.test	#Tool이름의 데이터베이스 생성
	
collection = db.get_collection('npcSpawnEdit')	#컬렉션 선택
if not collection:
	collection = db.npcSpawnEdit #npcSpawnEdit라는 이름의 컬렉션(테이블) 생성
print(db)
print(" ")
print(collection)

#db안에 컬렉션 리스트 출력
collection_list = db.collection_names() #선택된 데이터베이스의 collection 목록들을 출력
print(collection_list)	#가져오려면 인증 필요함.
print(" ")


#컬렉션 안의 document수 표시
print(collection.count())
print(" ")

#find
print("find ")
cursor = collection.find()
print(cursor)
print(" ")


print("for~~in~find ")
for result in collection.find():
        print(result)
        print(" ")

print("키와 값에 해당하는것, 첫번째 찾은것")
doc = collection.find_one({"level":"lv03"})
print(doc)


print("키와 값에 해당하는것, 모두")
docs = collection.find({"level":"lv03"})
for doc in docs:
    print(doc)


#insert
#insert는 deprecate, insert_one또는 대량 추가시는 insert_many사용
objectId = collection.insert_one({
    "user":"user1004",
    "level":"ti03",
    "territoryIdList":[2,5,7,23,45],
    "updatedTime" : "20200409-184332",
    "spawnNpc":
    {
        "3":
        {
            "1":
            {
                "pos":"327.0, 235.23, 433.344",
                "rot":"210.5",
                "prob":"3000",
                "dropId":128,
            },
            "2":"327.0, 235.23, 433.344"},
            "5":
            {
                "1":"327.0, 235.23, 433.344",
            "2":"327.0, 235.23, 433.344"},
            "23":
                {
                    "1":"327.0, 235.23, 433.344",
                    "2":"327.0, 235.23, 433.344"
                },
            }
        })

print(objectId)
print(" ")

#update
#update는 deprecate, replace_one, update_one, update_many중에 사용
#upsert - 데이터 존재시 없데이트, 없으면 insert, False로 주면 없으면 아무것도 안함.
collection.update({"user":"user1005"}, {"user":"user1006"}, upsert=True)

#멀티 업데이트
#해당 키값이 같은 원소는 모두 업데이트, 중복키 됨으로
#collection.update({"user":"user1005"}, {"user":"user1006"}, upsert=True, multiset=True)

#remove
#collection.remove({"user" : {"$eq":"user1004"}}) (edited) 