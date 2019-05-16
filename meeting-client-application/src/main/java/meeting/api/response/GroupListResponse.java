package meeting.api.response;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.List;

@Data
@NoArgsConstructor
public class GroupListResponse {

    private String flag;

    private List<GroupListItemResponse> items;
}
