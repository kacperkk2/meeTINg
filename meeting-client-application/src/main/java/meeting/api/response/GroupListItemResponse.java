package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class GroupListItemResponse {

    private long id;

    private String name;

    private String leader;
}
