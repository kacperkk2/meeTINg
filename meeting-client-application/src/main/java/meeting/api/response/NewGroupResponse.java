package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class NewGroupResponse {

    private long id;

    private String name;

    private String leader;
}
