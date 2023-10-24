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
			int choice = -1;
			String tableName = "Employee";

			while (choice != 0) {
				System.out.println("\n--- MENU ---");
				System.out.println("1. Select query");
				System.out.println("2. Create table");
				System.out.println("3. Insert query");
				System.out.println("4. Update query");
				System.out.println("5. Delete query");
				System.out.println("6. Exit");
				System.out.println("------------\n");

				System.out.println("Enter your choice:");
				choice = sc.nextInt();
				
				switch (choice) {
				case 1: // Select Query
					rs = st.executeQuery("select * from Employee");

					while (!rs.isLast()) {
						rs.next();
						int empid = rs.getInt("Emp_id");
						String empfname = rs.getString("Emp_fname");
						String emplname = rs.getString("Emp_lname");

						System.out.println("employee id: " + empid);
						System.out.println("employee name: " + empfname + " " + emplname);
					}

					System.out.println("END");

					break;

				case 2: // Create table

					break;

				case 3: // Insert Query
					Scanner sc3 = new Scanner(System.in);
					String query = "insert into " + tableName;
					
					System.out.println("Enter fields to insert into: (comma separated, enter * if all fields)");
					String fields = sc3.nextLine();
					
					if(fields != "*") {
						query += "(" + fields + ") ";
					}
					
					System.out.println("Enter values to insert: (comma separated)");
					String values = sc3.nextLine();
					query += "values(" + values + ");";

					System.out.println("Query> " + query);
					st.executeUpdate(query);
					System.out.println("Inserted data!");

					sc3.close();
					break;

				case 4: // Update Query

					break;

				case 5: // Delete Query

					break;

				case 6: // Exit
					System.out.println("Bye! :)");
					choice = 0;
					break;

				default: // Forced Exit
					System.out.println("Forced Exit!");

					choice = 0;
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
