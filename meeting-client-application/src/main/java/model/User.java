package model;

import enums.SystemRole;
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

    private SystemRole systemRole;
}
