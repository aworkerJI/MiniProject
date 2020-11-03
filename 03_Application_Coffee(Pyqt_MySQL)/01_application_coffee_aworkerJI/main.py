from PyQt5.QtWidgets import QApplication

from CoffeeApp.application_coffee_practice.ui.product import ProductUI

if __name__ == "__main__":
    app = QApplication([])
    w = ProductUI()
    app.exec_()

































    # w = SaleUI()
    # w = SaleUI()
    # w = SaledetailUI()


    # 19/12/16 select는 되니깐 select 먼저 UI 연결해 보자

    # saledao = SaleDao()     # 연결되는지 확인 해보고 나중에 UI 작업
    # prodao = ProductDao()   #

    # prodao.insert_item('B005', '카페라떼')            #product insert
    # prodao.delete_item('B005')                      #product delete
    # prodao.update_item('B005', '카페라떼2', 'B005')   #product update
    # prodao.select_item()                            #product select

    # saledao.insert_item('B003',5000, 500, 50)       #sale insert
    # saledao.delete_item(6)                          #sale delete
    # saledao.update_item('B003', 5555, 555, 55, 6)   #sale update
    # saledao.select_item()                           #sale select


    # 추상클래스 쓰지않고 그냥 썼을때
    # pool = ConnectionPool.get_instance()
    # connection = pool.get_connection()
    # print(pool, connection)
    # pdt = ProductDao()
    # pdt.insert_product()
    # pdt.delete_product()
    # pdt.select()
    # pdt.update_product()


