using System;
using System.Data;
using System.Data.SqlClient;
using System.Threading;

namespace Deadlock
{
    internal class Program
    {
        static string connectionString = "Data Source=LAPTOP-Q3R7T602\\SQLEXPRESS; Initial Catalog=MagazinHaine; Integrated Security=True; ";
        const int MaxRetries = 3;

        static void ExecuteWithRetry(string procName)
        {
            int attempt = 0;
            bool success = false;

            while (attempt < MaxRetries && !success)
            {
                attempt++;
                try
                {
                    using (var conn = new SqlConnection(connectionString))
                    using (var cmd = new SqlCommand(procName, conn))
                    {
                        cmd.CommandType = CommandType.StoredProcedure;
                        conn.Open();
                        using (var reader = cmd.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                Console.WriteLine($"[{procName}] Success (attempt {attempt}): {reader[0]}");
                                success = true;
                            }
                        }
                    }
                }
                catch (SqlException ex)
                {
                    if (ex.Number == 1205) // Deadlock
                    {
                        Console.WriteLine($"[{procName}] Deadlock detected. Retrying... ({attempt}/{MaxRetries})");
                       
                    }
                    else
                    {
                        Console.WriteLine($"[{procName}] SQL Error: {ex.Message}");
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"[{procName}] General Error: {ex.Message}");
                    break;
                }
            }

            if (!success)
                Console.WriteLine($"[{procName}] Aborted after {MaxRetries} failed attempt(s).");
        }

        static void Main(string[] args)
        {
            for (int round = 1; round <= 5; round++)
            {
                Console.WriteLine($"\n--- ROUND {round} ---");

                Thread t1 = new Thread(() => ExecuteWithRetry("DeadLock1"));
                Thread t2 = new Thread(() => ExecuteWithRetry("DeadLock2"));

                t1.Start();
                t2.Start();

                t1.Join();
                t2.Join();
            }

            Console.WriteLine("\nDone.");
            Console.ReadLine();
        }
    
}
}
