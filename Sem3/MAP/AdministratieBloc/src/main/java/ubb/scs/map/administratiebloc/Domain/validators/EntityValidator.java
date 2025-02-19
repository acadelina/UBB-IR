package ubb.scs.map.administratiebloc.Domain.validators;

import ubb.scs.map.administratiebloc.Domain.Entity;

public class EntityValidator implements Validator <Entity> {

    @Override
    public void validate(Entity entity) throws ValidationException {
        if(entity.getId()==null)
            throw new ValidationException("Entity must have an ID");
    }
}
