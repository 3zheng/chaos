CREATE PROCEDURE [dbo].[set_user_match_info]
	@user_id bigint,
	@plan_id int,
	@match_id bigint,
	@plan_name nvarchar(50),
	@match_rank int,
	@end_date bigint
AS
	insert into user_match_info(user_id, plan_id, match_id, plan_name, match_rank, end_date)
		values(@user_id, @plan_id, @match_id, @plan_name, @match_rank, @end_date)
RETURN 0
