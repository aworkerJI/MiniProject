import inspect
from abc import ABCMeta, abstractmethod

# from mysql.connector import Error
from mysql.connector import Error

from CoffeeApp.application_coffee_practice.db_connection.connection_pool_ import ConnectionPool


class Dao(metaclass= ABCMeta): # 추상클래스
    def __init__(self):
        self.connection_pool = ConnectionPool.get_instance()

    @abstractmethod     # 추상 메소드
    def insert_item(self, **kwargs):        # **kwargs 딕셔너리 형태.(파이썬 개발자들 정의)
        raise NotImplementedError("Subclass must implement abstract method")

    @abstractmethod     # 추상 메소드
    def update_item(self, **kwargs):
        raise NotImplementedError("Subclass must implement abstract method")

    @abstractmethod     # 추상 메소드
    def delete_item(self, **kwargs):
        raise NotImplementedError("Subclass must implement abstract method")

    @abstractmethod     # 추상 메소드
    def select_item(self, **kwargs):
        raise NotImplementedError("Subclass must implement abstract method")

    def do_query(self, **kwargs):         # 추상 메소드 아님, 다른 것들은 상속 받기
        print("\n_______{}()______".format(inspect.stack()[0][3])) # inspect.stack 현재 실행하고 있는 함수 이름
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            print("do_query cursor실행")
            if kwargs['kargs'] is not None:
                cursor.execute(kwargs['query'], kwargs['kargs'])
            else:
                cursor.execute(kwargs['query'])
            conn.commit()
        except Error as e:
            print(e)
            raise e
        finally:
            cursor.close()
            conn.close()

    def iter_row(self,cursor, size=5):
        while True:
            rows = cursor.fetchmany(size)
            if not rows:
                break
            for row in rows:
                yield row

    def iter_row_order(self, cursor):
        for result in cursor.stored_results(): # 프로시저 결과 가져오기
            rows = result.fetchall()
            if not rows:
                break
            for row in rows:
                yield row