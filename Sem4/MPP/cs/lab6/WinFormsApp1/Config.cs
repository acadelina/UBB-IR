using System.Configuration;

static class Config
{
    public static string GetConnectionStringByName(string name)
        => ConfigurationManager.ConnectionStrings[name]?.ConnectionString;
    
    public static readonly IDictionary<string, string> DatabaseProperties = new Dictionary<string, string>
    {
        { "ConnectionString",  GetConnectionStringByName("festival") },
       
    };
}