package ubb.scs.map.demo3.domain;

public interface Validator<T> {
    void validate(T entity) throws ValidationException;
}