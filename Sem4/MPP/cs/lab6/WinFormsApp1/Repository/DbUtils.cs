using System.Data;
using Domain;
using log4net;

namespace Repository;

public abstract class DbUtils<ID,E> where E:Entity<ID>
{
    private static readonly ILog log=LogManager.GetLogger("DbUtils");
    private IDictionary<string, string> Properties;

    protected DbUtils(IDictionary<string, string> properties)
    {
        Properties = properties;
        log.Info("DbUtils constructor called");
    }
    
    protected abstract E DecodeReader(IDataReader reader);
    

    protected int ExecuteNonQuery(string sql, Dictionary<string, object> parameters = null)
    {
        log.Info($"Executing NonQuery: {sql}");
        var con = ConnUtils.getConnection(Properties);
        

            using (var command = con.CreateCommand())
            {
                command.CommandText = sql;
                if (parameters != null)
                {
                    foreach (var p in parameters)
                    {
                        var parameter = command.CreateParameter();
                        parameter.ParameterName = p.Key;
                        parameter.Value = p.Value;
                        command.Parameters.Add(parameter);
                    }
                }

                return command.ExecuteNonQuery();
            }

    }

    protected IEnumerable<E> Select(string sql, Dictionary<string, object> parameters = null)
    {
        log.Info($"Executing Select: {sql}");
        var results = new List<E>();
        var con = ConnUtils.getConnection(Properties);
        

            using (var command = con.CreateCommand())
            {
                command.CommandText = sql;
                if (parameters != null)
                {
                    foreach (var p in parameters)
                    {
                        var parameter = command.CreateParameter();
                        parameter.ParameterName = p.Key;
                        parameter.Value = p.Value;
                        command.Parameters.Add(parameter);
                    }
                }

                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                        results.Add(DecodeReader(reader));
                }
            }
            
        
        
        log.Info($"Done Select: {sql}");
        return results;
    }

    protected E SelectFirst(string sql, Dictionary<string, object> parameters = null)
    {
        var con = ConnUtils.getConnection(Properties);
        {
            using (var command = con.CreateCommand())
            {
                command.CommandText = sql;
                if (parameters != null)
                {
                    foreach (var p in parameters)
                    {
                        var parameter = command.CreateParameter();
                        parameter.ParameterName = p.Key;
                        parameter.Value = p.Value;
                        command.Parameters.Add(parameter);
                    }
                }

                using (var reader = command.ExecuteReader())
                {
                    if (!reader.Read())
                        return default;
                    return DecodeReader(reader);
                }
            }
        }
    }
}