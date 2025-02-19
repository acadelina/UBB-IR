package ubb.scs.map.socialNetwork.service;

import ubb.scs.map.socialNetwork.domain.Post;
import ubb.scs.map.socialNetwork.repository.file.PostDBRepository;

import java.util.ArrayList;
import java.util.List;

public class ServicePost {
    private PostDBRepository repo;
    public ServicePost(PostDBRepository repo) {
        this.repo = repo;
    }
    public List<Post> getAllPosts() {
        List<Post> posts = new ArrayList<Post>();

        repo.findAll().forEach(post -> posts.add(post));
        return posts;
    }

    public Post getPost(Long id) {
        if(repo.findOne(id).isPresent()) {
            return repo.findOne(id).get();
        };
        return null;
    }
    public void createPost(Post post) {
        repo.save(post);
    }
    public void deletePost(Long id) {
        repo.delete(id);
    }
}
