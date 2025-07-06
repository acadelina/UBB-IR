using Domain;

namespace Repository;

public interface Repository<TID, TEntity> where TEntity : Entity<TID>
{
    List<TEntity> GetAll();
    TEntity GetOne(TID id);
    void Add(TEntity entity);
    void Update(TEntity entity);
    void Delete(TEntity entity);
    
}