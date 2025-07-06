using System.Data;
using ConnectionUtils;
using Microsoft.Data.Sqlite;

namespace ConsoleApp1.Repository;

public class SqlitesConFactory:ConnectionFactory
{
    public override IDbConnection createConnection(IDictionary<string,string> props)
    {
        
        String connectionString = props["ConnectionString"];
        Console.WriteLine("SQLite ---Se deschide o conexiune la  ... {0}", connectionString);
        return new SqliteConnection(connectionString);

    }
}