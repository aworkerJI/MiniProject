import inspect
from mysql.connector import Error

from CoffeeApp.application_coffee_practice.dao.abs_dao import Dao

select_sql = "select no, sale_price, addTax, supply_price, marginPrice from sale_detail"

class SaleDetailDao(Dao):
    def insert_item(self, code=None, name=None):
        pass

    def update_item(self, code=None, name=None):
        pass

    def delete_item(self, code=None):
        pass

    def select_item(self, code=None):
        print("\n_____ {}(saledetail) _____".format(inspect.stack()[0][3]))
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.execute(select_sql)
            res = []
            [res.append(row) for row in self.iter_row(cursor, 5)]
            #print(res)
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()

    def orderby_saleprice_asc(self):
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.callproc("proc_saledetail_sale_price_asc")
            res = []
            [res.append(row) for row in self.iter_row_order(cursor)]
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()

    def orderby_saleprice_desc(self):
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.callproc("proc_saledetail_sale_price_desc")
            res = []
            [res.append(row) for row in self.iter_row_order(cursor)]
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()

    def orderby_marginprice_asc(self):
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.callproc("proc_saledetail_marginPrice_asc")
            res = []
            [res.append(row) for row in self.iter_row_order(cursor)]
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()

    def orderby_marginprice_desc(self):
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.callproc("proc_saledetail_marginPrice_desc")
            res = []
            [res.append(row) for row in self.iter_row_order(cursor)]
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()



