package model;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
@Builder
public class User {

    private long id;

    private String username;

    private String password;

    private boolean isLeader;
}
