CREATE PROCEDURE [dbo].[set_user_fund]
	@user_id bigint,
	@fund_id int,
	@fund_count bigint 
AS
	SET NOCOUNT ON
--修改或者新增用户的财富表记录
	
	update user_fund set fund_count = @fund_count, up_code = up_code + 1, modify_time = getdate() where user_id = @user_id and fund_id = @fund_id;
	if @@ROWCOUNT = 0
	begin
            insert user_fund(user_id, fund_id,  fund_count, up_code, modify_time)
					values(@user_id,  @fund_id, @fund_count, 1,      getdate());
	end
RETURN 0

