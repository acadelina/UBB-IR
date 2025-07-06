using System.Data;


namespace Repository;

public static class ConnUtils
{
    private static IDbConnection instance = null;
    
    public static IDbConnection getConnection(IDictionary<string, string> properties)
    {
        
        if (instance == null || instance.State == ConnectionState.Closed || instance.State == ConnectionState.Broken)
        {
            instance=getNewConnection(properties);
            instance.Open();
        }
        return instance;
    }
   


    private static IDbConnection getNewConnection(IDictionary<string, string> properties)
    {
        return ConnectionUtils.ConnectionFactory.getInstance().createConnection(properties);
    }
    
   
   
}