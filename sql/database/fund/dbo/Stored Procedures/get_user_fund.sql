CREATE PROCEDURE [dbo].[get_user_fund]
	@user_id bigint
AS
	SET NOCOUNT ON
--取该用户id的所有财富记录
	select fund_id, fund_count from user_fund
	where user_id = @user_id;
RETURN 0
