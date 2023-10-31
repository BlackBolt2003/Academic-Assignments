package mypack;

import java.sql.*;
import java.util.*;

public class MySqlConnectivity {

	public static void main(String[] args) throws Exception {
		System.out.println("Checking connection...");
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			Connection con = DriverManager.getConnection("jdbc:mysql://10.10.15.233/te31485db", "te31485", "te31485");

			Statement st = con.createStatement();
			ResultSet rs;

			if (con != null && !con.isClosed()) {
				System.out.println("Database Connected\n");
			} else {
				System.out.println("Database not connected");
			}

			Scanner sc = new Scanner(System.in);
			String tableName = "Food";
			boolean cont = true;

			String query, fields, values, clause;

			while (cont) {
				System.out.println("\n--- MENU ---");
				System.out.println("1. Select query");
				System.out.println("2. Create table");
				System.out.println("3. Insert query");
				System.out.println("4. Update query");
				System.out.println("5. Delete query");
				System.out.println("6. Exit");
				System.out.println("------------\n");

				System.out.println("Enter your choice:");
				int choice = 0;
				if (sc.hasNext()) {
					choice = sc.nextInt();
				}

				switch (choice) {
					case 1: // Select Query

						rs = st.executeQuery("select * from Food");

						System.out.println("id \t name \t price");

						while (!rs.isLast()) {
							rs.next();
							int id = rs.getInt("id");
							String name = rs.getString("name");
							String price = rs.getString("price");

							System.out.println(id + " \t " + name + " \t " + price);
						}

						break;

					case 2: // Create table
						Scanner sc2 = new Scanner(System.in);
						query = "create table  ";

						System.out.println("Enter table name: ");
						tableName = sc2.nextLine();

						query += tableName + "(";

						System.out.println("Enter fields: (e.g id int primary key, ...)");
						fields = sc2.nextLine();

						query += fields + ");";

						st.execute(query);
						System.out.println("Created table " + tableName);

						sc2.close();
						break;

					case 3: // Insert Query
						Scanner sc3 = new Scanner(System.in);
						query = "insert into " + tableName;

						System.out.println("Enter fields to insert into: (comma separated, enter * if all fields)");
						fields = sc3.nextLine();

						if (fields != "*") {
							query += "(" + fields + ") ";
						}

						System.out.println("Enter values to insert: (comma separated)");
						values = sc3.nextLine();
						query += "values(" + values + ");";

						System.out.println("Query> " + query);
						st.executeUpdate(query);
						System.out.println("Inserted data!");

						sc3.close();
						break;

					case 4: // Update Query
						Scanner sc4 = new Scanner(System.in);
						query = "update " + tableName;

						System.out.println("Enter field to update: ");
						fields = sc4.nextLine();

						query += " set " + fields + " = ";

						System.out.println("Enter new value: ");
						values = sc4.nextLine();
						query += values;

						System.out.println("Enter condition: (e.g. name = 'pizza' | * if none)");
						clause = sc4.nextLine();

						if (clause != "*") {
							query += " where " + clause + ";";
						}

						System.out.println("Query> " + query);
						st.executeUpdate(query);
						System.out.println("Updated data!");

						sc4.close();
						break;

					case 5: // Delete Query
						Scanner sc5 = new Scanner(System.in);
						query = "delete from " + tableName;

						System.out.println("Enter condition: (e.g. Emp_fname = 'pizza' | * if none)");
						clause = sc5.nextLine();

						if (clause != "*") {
							query += " where " + clause + ";";
						}

						System.out.println("Query> " + query);
						st.executeUpdate(query);
						System.out.println("Deleted row!");

						sc5.close();
						break;

					case 6: // Exit
						System.out.println("Bye! :)");
						cont = false;
						break;

					default: // Forced Exit
						System.out.println("Forced Exit!");
						cont = false;
						System.exit(0);
						break;
				}
			}

			sc.close();
			st.close();
			con.close();

		} catch (Exception e) {
			System.out.println("\nError occurred!\n");
			System.out.println(e);
		}
	}

}