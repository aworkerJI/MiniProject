import inspect
# from mysql.connector import Error
from mysql.connector import Error

from CoffeeApp.application_coffee_practice.dao.abs_dao import Dao

insert_sql = "Insert into product values( %s, %s)"
update_sql = "UPDATE product SET name =%s WHERE code=%s"
delete_sql = "DELETE FROM product WHERE code = %s"
select_sql = "SELECT code, name FROM product"
select_sql_where = select_sql + " WHERE code=%s"

class ProductDao(Dao):
    def insert_item(self, code = None, name = None):
        print("\n_____ {}() _____".format(inspect.stack()[0][3]))
        args = (str.upper(code), name)
        try:
            super().do_query(query=insert_sql, kargs=args)
            return True
        except Error:
            return False

    def update_item(self, name = None, code = None):
        print("\n_____ {}() _____".format(inspect.stack()[0][3]))
        args = (name, code)
        try:
            self.do_query(query=update_sql, kargs=args)
            return True
        except Error:
            return False

    def delete_item(self, code = None):
        print("\n_____ {}() _____".format(inspect.stack()[0][3]))
        args = (code,)
        try:
            self.do_query(query=delete_sql, kargs=args)
            return True
        except Error:
            return False

    def select_item(self, code = None):
        print("\n_____ {}(product) _____".format(inspect.stack()[0][3]))
        try:
            conn = self.connection_pool.get_connection()
            cursor = conn.cursor()
            cursor.execute(select_sql) if code is None else cursor.execute(select_sql_where, (code,))
            res = []
            [res.append(row) for row in self.iter_row(cursor, 5)]
            return res
        except Error as e:
            print(e)
        finally:
            cursor.close()
            conn.close()



