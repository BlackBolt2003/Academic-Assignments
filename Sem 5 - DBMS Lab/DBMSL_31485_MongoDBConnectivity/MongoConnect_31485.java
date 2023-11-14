import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;
import java.util.Scanner;

public class MongoConnect {
    public static void main(String[] args) {
        MongoClient mongoClient = new MongoClient("localhost", 27017); // Connect to MongoDB server
        MongoDatabase database = mongoClient.getDatabase("FoodDB");
        MongoCollection<Document> collection = database.getCollection("FoodCollection");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Add Record");
            System.out.println("2. Edit Record");
            System.out.println("3. Delete Record");
            System.out.println("4. List Records");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");

            int choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    // Add Record
                    System.out.print("Enter key: ");
                    String key = scanner.next();
                    System.out.print("Enter value: ");
                    String value = scanner.next();

                    Document document = new Document("key", key).append("value", value);
                    collection.insertOne(document);
                    System.out.println("Record added successfully.");
                    break;

                case 2:
                    // Edit Record
                    System.out.print("Enter key to edit: ");
                    String editKey = scanner.next();
                    System.out.print("Enter new value: ");
                    String newValue = scanner.next();

                    collection.updateOne(new Document("key", editKey),
                            new Document("$set", new Document("value", newValue)));
                    System.out.println("Record updated successfully.");
                    break;

                case 3:
                    // Delete Record
                    System.out.print("Enter key to delete: ");
                    String deleteKey = scanner.next();
                    collection.deleteOne(new Document("key", deleteKey));
                    System.out.println("Record deleted successfully.");
                    break;

                case 4:
                    // List Records
                    MongoCursor<Document> cursor = collection.find().iterator();
                    while (cursor.hasNext()) {
                        Document doc = cursor.next();
                        System.out.println("Key: " + doc.getString("key") + " Value: " + doc.getString("value"));
                    }
                    cursor.close();
                    break;

                case 5:
                    // Exit
                    mongoClient.close();
                    System.out.println("Exiting the program.");
                    System.exit(0);
                    break;

                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }
}
