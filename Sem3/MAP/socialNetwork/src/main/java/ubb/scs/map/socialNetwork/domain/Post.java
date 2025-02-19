package ubb.scs.map.socialNetwork.domain;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Post extends Entity<Long> {
    private String description;
    private LocalDateTime date;
    private byte[] image;
    private String author;
    private List<String> likes;
    private int likesCount;


    public Post(byte[] image, String description,String author) {
        this.image = image;
        this.description = description;
        this.author = author;
        this.likes = new ArrayList<>();
        this.likesCount = 0;
        this.date = LocalDateTime.now();

    }
    public Post(byte[] image, String description,String author, List<String> likes,LocalDateTime date) {
        this.image = image;
        this.description = description;
        this.author = author;
        this.likes = likes;
        this.date = date;
        this.likesCount = likes.size();

    }
    public String getDescription() {
        return description;
    }
    public void setDescription(String description) {
        this.description = description;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public byte[] getImage() {
        return image;
    }

    public void setImage(byte[] image) {
        this.image = image;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public List<String> getLikes() {
        return likes;
    }

    public void setLikes(List<String> likes) {
        this.likes = likes;
    }

    public int getLikesCount() {
        return likesCount;
    }

    public void setLikesCount(int likesCount) {
        this.likesCount = likesCount;
    }


}
